/*
 * mainmenu.c
 *
 *  Created on: Jun 5, 2025
 *      Author: mjayakumar
 */


#include "mainmenu.h"



char *mainMenuMsg = "\r\r\r\r\n=================================\r\n|     Menu   |\r\n=================================\r\nPress [1] Led Effect\r\nPress [2] Date and Time\r\nPress [3] Exit\r\nEnter your Choice Here => ";


void mainMenu(void) {

	uint32_t cmd_addr;
	uint32_t task;
	command_t *cmd;
	BaseType_t retstatus;

	while (1) {
	retstatus = xQueueSend(print_q,&mainMenuMsg, portMAX_DELAY);

	if (retstatus != pdPASS) {
		printf("Main Menu Send to the Consle was Failed \n");
		return;
	}

	retstatus = xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY);
	if (retstatus == pdFAIL) {
		printf(" Notification  Receive was Failed\n");
		return;
	}



	cmd = (command_t*)cmd_addr;

	task = cmd->playload[0];

	if( (task < 1) || (task > 3) ) {
		continue;
	}

	switch( task ) {
	case 1:
		xTaskNotify(ledTask,0,eNoAction);
		currentState = sLedEffect;
		break;
	case 2:
		xTaskNotify(rtcTask,0,eNoAction);
		currentState = sRtcMenu;
		break;
	case 3:
		printf(" Exiting the Application \n");
		break;
	}
	xTaskNotifyStateClear(menuTask);
	retstatus = xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
	if( retstatus == pdFAIL){
		printf(" NOtify Was Failed \n");
		return;
	}

	}

}
