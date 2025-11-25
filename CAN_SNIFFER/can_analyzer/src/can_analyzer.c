/*
 * can_analyzer.c
 *
 *  Created on: Nov 22, 2025
 *      Author: mjayakumar
 */
#include "can_analyzer.h"
#include <string.h>
#include "usb_device.h"
#include "usbd_cdc_if.h"

extern USBD_HandleTypeDef hUsbDeviceHS;
static CAN_RxHeaderTypeDef rxHeaderit;
static uint8_t rx_buffer[8];
uint8_t usb_rx_buffer[256];
uint32_t usb_rx_len;
static uint8_t rx_status_flag;


static char *mainmenu =    "\r\n ========================= MAIN MENU ========================\r\n"
						   "[1] Read Data from CAN Bus\r\n"
						   "[2] Write Data to CAN Bus\r\n"
					       "[3] Read Data from specific Node in CAN Bus\r\n"
						   "Enter the choice : \n";


static Status_t (*pfpointer[3])(can_analyzer_handle_t *) = {can_analyzer_idle_state,can_analyzer_write_state,can_analyzer_read_state};


Status_t can_analyzer_init(can_analyzer_handle_t *phandler){
	phandler->state_handler.current_state =IDEAL;
	phandler->len = 0;
	phandler->identifier = 0;
	phandler->broadcast = CAN_NODE_BROADCAST_ENABLE;
	memset(phandler->data,0,sizeof(*phandler->data));

	while(hUsbDeviceHS.dev_state != USBD_STATE_CONFIGURED) {
		HAL_Delay(10);
	}

	HAL_Delay(3000);

	printlog(mainmenu);
	return STATUS_OK;
}

Status_t can_analyzer_statemachine(can_analyzer_handle_t *phandler) {
	if (!phandler) {
		return STATUS_NULL_POINTER;
	}

	return  ( pfpointer[phandler->state_handler.current_state](phandler));
}

Status_t can_analyzer_read(can_analyzer_handle_t *phandler) {

	if (!phandler->data) {
		return STATUS_NULL_POINTER;
	}

	if(!rx_status_flag) {
		return STATUS_NODATA;
	}

	memcpy(phandler->data,rx_buffer,phandler->len);
	memcpy((void *)phandler->can.pcanRxheader,(void *)&rxHeaderit,sizeof(rxHeaderit));
	return STATUS_OK;
}

Status_t can_analyzer_write(can_analyzer_handle_t *phandler) {

	if (!phandler->data) {
		return STATUS_NULL_POINTER;
	}

	if (phandler->len <= 8) {

		phandler->can.pcanTxheader->DLC = phandler->len;
		if (HAL_CAN_AddTxMessage(phandler->can.pcan, phandler->can.pcanTxheader,
				(uint8_t*) phandler->data, phandler->can.pTxMailbox)
				== HAL_ERROR) {
			return STATUS_FAILED;
		}
	} else {
		for (int i = 0; i < phandler->len; i+=8) {
			phandler->can.pcanTxheader->DLC = 8;
			if (HAL_CAN_AddTxMessage(phandler->can.pcan,
					phandler->can.pcanTxheader, (uint8_t*) phandler->data,
					phandler->can.pTxMailbox) == HAL_ERROR) {
				return STATUS_FAILED;
			}
			phandler->data += 8;
		}
	}

	return STATUS_OK;
}

Status_t can_analyzer_set_config(can_analyzer_handle_t *phandler) {

	uint16_t filter_id = (phandler->broadcast) ? 0xFFFF:phandler->identifier;

	phandler->can.pcanconfig->FilterActivation = CAN_FILTER_ENABLE;
	phandler->can.pcanconfig->FilterBank = 0;
	phandler->can.pcanconfig->FilterFIFOAssignment = CAN_FILTER_FIFO0;

	phandler->can.pcanconfig->FilterIdHigh = filter_id << 5;
	phandler->can.pcanconfig->FilterIdLow = 0x0000;

	phandler->can.pcanconfig->FilterMaskIdHigh = filter_id << 5;
	phandler->can.pcanconfig->FilterMaskIdLow = 0x0000;

	phandler->can.pcanconfig->SlaveStartFilterBank = 20;
	phandler->can.pcanconfig->FilterMode = CAN_FILTERMODE_IDMASK;
	phandler->can.pcanconfig->FilterScale = CAN_FILTERSCALE_16BIT;


	if ( HAL_CAN_ConfigFilter(phandler->can.pcan, phandler->can.pcanconfig) != HAL_OK ) {
		return STATUS_FAILED;
	}
	if ( HAL_CAN_Start(phandler->can.pcan) != HAL_OK) {
		return STATUS_FAILED;
	}

	return STATUS_OK;
}

Status_t can_analyzer_read_state(can_analyzer_handle_t *phandler) {

	Status_t ret;

	if ((!phandler->can.pcan) || (!phandler->can.pcanRxheader)
			|| (!phandler->can.pcanconfig)) {
		return STATUS_NULL_POINTER;
	}

	printlog("Trying to configure the CAN Module .......\r\n");

	if (can_analyzer_set_config(phandler) != STATUS_OK) {
		printlog("ERROR :: Failed to Configure the Can Module \r\n");
		printlog(mainmenu);
		phandler->state_handler.current_state = IDEAL;
		return STATUS_FAILED;
	}

	printlog("Module Get configured Successfully\r\n");

	printlog(
			"=========================================<CAN READ START>========================================\r\n");
	printlog(
			"========================= Note : To STOP the read function Press E or e ==========================\r\n");

	if (phandler->broadcast == CAN_NODE_BROADCAST_DISABLE) {

		printlog("Enter the Identifier to Filter \r\n");

		do {
			if (usb_rx_len > 0) {
				usb_rx_len = 0;
				phandler->identifier = atoi((const char*) usb_rx_buffer);

				if (phandler->identifier <= 0) {
					printlog("ERROR:: Invalid Identifier for filter\r\n");
					phandler->state_handler.current_state = IDEAL;
					memset(usb_rx_buffer, '\0', sizeof(usb_rx_buffer));
					usb_rx_len = 0;
					return STATUS_FAILED;
				}
				memset(usb_rx_buffer, '\0', sizeof(usb_rx_buffer));
			}
		} while (!usb_rx_len);
	}
	while (1) {

		if (usb_rx_len > 0) {
			usb_rx_len = 0;
			if ((usb_rx_buffer[0] == 'E') || (usb_rx_buffer[0] == 'e')) {
				break;
			}
		}

		ret = can_analyzer_read(phandler);
		if (ret == STATUS_FAILED) {
			printlog(mainmenu);
			phandler->state_handler.current_state = IDEAL;
			printlog("ERROR ::CAN Receiver Failed \r\n");
			return STATUS_FAILED;
		} else if (ret == STATUS_NODATA) {
			printlog("No Can Node in the Bus \r\n");
		} else {
			CDC_Transmit_HS(phandler->data, phandler->len);
			HAL_Delay(500);
		}
	}

	if (HAL_CAN_Stop(phandler->can.pcan) != HAL_OK) {
		return STATUS_FAILED;
	}
	memset(usb_rx_buffer, '\0', sizeof(usb_rx_buffer));
	printlog(mainmenu);
	phandler->state_handler.current_state = IDEAL;
	return ret;
}

Status_t can_analyzer_idle_state(can_analyzer_handle_t *phandler) {

	uint32_t user_state;

	phandler->state_handler.current_state = IDEAL;

	if (phandler->len > 0) {
		phandler->len = 0;
		memset(phandler->data, '\0', sizeof(*phandler->data));
		memset(rx_buffer, 0, sizeof(rx_buffer));
	}

	if (usb_rx_len > 0) {
		usb_rx_buffer[usb_rx_len] = '\0';
		user_state = atoi((const char*) usb_rx_buffer);
		usb_rx_len = 0;

		switch (user_state) {
		case 1:
			phandler->state_handler.current_state = RECEIVE;
			phandler->len = 8;
			break;
		case 2:
			phandler->state_handler.current_state = TRANSMIT;
			break;
		case 3:
			phandler->broadcast = CAN_NODE_BROADCAST_DISABLE;
			phandler->state_handler.current_state = RECEIVE;
		}
		user_state = 0;
		memset(usb_rx_buffer, '\0', sizeof(usb_rx_buffer));
	}
	return STATUS_OK;
}

/*
 * TO Do here we are facing the bug while getting the error and also this was not a
 * stable version of can analyzer we need to enhance the usb communication CDC .
 *
 */
Status_t can_analyzer_write_state(can_analyzer_handle_t *phandler) {


	char log_buffer[125];
	int32_t identifier = 0;
	int32_t data_len = 0;
	uint32_t itteration = 0;
	uint32_t timeout = 0;

	printlog(
			"\r\n =============================== Write Menu ==================================\r\n");

	printlog("\r\n Enter the Identifier Id => \r");
	usb_rx_len = 0;

	do {
		if (usb_rx_len > 0) {
			identifier = atoi((const char*) usb_rx_buffer);
			if (identifier < 0) {
				printlog(
						"ERROR :: Invalid Identifier Can Sniffer goes to Idle Mode Try Agian \r\n");
				printlog(mainmenu);
				phandler->state_handler.current_state = IDEAL;
				return STATUS_FAILED;
			}
		}
	} while (!usb_rx_len);
	usb_rx_len = 0;

	memset(usb_rx_buffer, '\0', sizeof(usb_rx_buffer));


	printlog("\r\n Enter the Length => \r");

	do {
		if (usb_rx_len > 0) {
			data_len = atoi((const char*) usb_rx_buffer);

			if ((data_len < 0) || (data_len > 256)) {
				printlog(
						"ERROR :: Invalid Data length Can Sniffer goes to Idle Mode Try Agian \r\n");
				printlog(mainmenu);
				phandler->state_handler.current_state = IDEAL;
				return STATUS_FAILED;
			}
		}
	} while (!usb_rx_len);
	usb_rx_len = 0;
	memset(usb_rx_buffer,'\0',sizeof(usb_rx_buffer));


	printlog("Enter the Data To Send on CAN BUS \r\n");
	while(itteration < data_len) {

		sprintf(log_buffer,"Data %ld => \r",itteration + 1);
		printlog(log_buffer);

		if(usb_rx_len > 0) {
				((uint8_t *)phandler->data)[itteration++] = usb_rx_buffer[0];
				usb_rx_len = 0;
				timeout = 0;
			}

		timeout++;

		if(timeout == 2000) {
			timeout = 0;
			printlog("ERROR:: Time out \r\n");
			printlog(mainmenu);
			phandler->state_handler.current_state = IDEAL;
			return STATUS_TIMEOUT;
		}
		HAL_Delay(250);
	}

	memset(usb_rx_buffer,'\0',sizeof(usb_rx_buffer));


	phandler->can.pcanTxheader->RTR = CAN_RTR_DATA;
	phandler->can.pcanTxheader->IDE = CAN_ID_STD;
	phandler->can.pcanTxheader->StdId = identifier;


	sprintf(log_buffer,"CAN Tx Configuration was Set to \r\n Identifier = > 0x%lx \r\n",identifier);
	printlog(log_buffer);

	memset(log_buffer,'\0',sizeof(log_buffer));

	printlog("Data => ");

	for(int i = 0; i < phandler->len; i++) {
		sprintf(log_buffer," 0x%x ",((uint8_t *)phandler->data)[i]);
		printlog(log_buffer);
	}
	printlog("\r\n");

	printlog("Data was Sending....................\r\n");

	if( can_analyzer_write(phandler) != STATUS_OK ) {
		phandler->state_handler.current_state = IDEAL;
		printlog(mainmenu);
		printlog("ERROR :: Transmission was Failed  \r\n");
		return STATUS_FAILED;
	}

	printlog("Data was send successfully \r\n");

	printlog(mainmenu);
	phandler->state_handler.current_state = IDEAL;

	memset(phandler->data,'\0',phandler->len);

	return STATUS_OK;
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeaderit, rx_buffer);
	if (rxHeaderit.DLC > 0 )
	{
		rx_status_flag = 1;
	}
}

void printlog(char *str) {
	uint32_t len = strlen(str);
	CDC_Transmit_HS((uint8_t *)str, len);
	HAL_Delay(150);
}

