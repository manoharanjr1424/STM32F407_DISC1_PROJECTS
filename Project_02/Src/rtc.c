/*
 * rtc.c
 *
 *  Created on: Jun 5, 2025
 *      Author: mjayakumar
 */

#include "rtc.h"

char printBuffer[150] = {0};

char *rtcMenu = "\r\r\r\r\n==================== RTC MENU ======================\r\n[1] Get Time \r\n[2] Get Date \r\n[3] Set Time\r\n[4] Set Date \r\n Enter Choice : ";
char *timeMenu = "\r\r\r\r\nEnter Time in Hrs:Min:Sec format \r\r\r\r\n Enter Time : ";
char *dateMenu = "\r\r\r\r\nEnter Date in Date/Month/Year \r\r\r\r\nEnter Data : ";
char *statusMenu[] = {"\r\r\r\r\nSuccessfully Completed","\r\r\r\r\nFailed to Write \r\r\r\r\n","\r\r\r\r\nFailed to Read\r\r\r\r\n"};

void RTCMenu(void) {
	uint32_t cmd_base;
	TaskHandle_t retStatus;
	command_t *cmd = NULL;
	uint32_t option;

	xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

	xQueueSend(print_q,&rtcMenu,portMAX_DELAY);

	xTaskNotifyWait(0,0,&cmd_base,portMAX_DELAY);

	cmd = (command_t *)cmd_base;

	if( (cmd->playloadLength < 1) || (cmd->playloadLength > 1)) {
		xQueueSend(print_q,&invalidMsg,portMAX_DELAY);
		return;
	}

	option =(uint32_t)(cmd->playload[0]);

	switch(option){
	case 1:
		getTimeData(printBuffer);
		break;
	case 2:
		getDateData(printBuffer);
		break;
	case 3:
		xQueueSend(print_q,&timeMenu,portMAX_DELAY);
		xTaskNotifyWait(0,0,&cmd_base,portMAX_DELAY);
		cmd = (command_t *)cmd_base;
		if( cmd == NULL) {
			printf("Data was Not Received from the User \n");
			break;
		}
		timeCommandExtracter(cmd);
		break;
	case 4:
		xQueueSend(print_q,&dateMenu,portMAX_DELAY);
		xTaskNotifyWait(0,0,&cmd_base,portMAX_DELAY);
		cmd = (command_t *)cmd_base;
		if( cmd == NULL) {
			printf("Data was Not Received from the User \n");
		}
		dateCommandExtracter(cmd);
		break;
	}

	xTaskNotify(menuTask,0,eNoAction);
	currentState = sMainMenu;
}



int8_t RTCInit(void) {
	gpio_handler_t sda, scl;
	i2c_handler_t i2c;

	sda.port = GPIOB;
	sda.pin = 7;
	sda.Afmode = SET_PIN_AF4;
	sda.pull_up_down = SET_PIN_PULLUP;
	sda.mode = SET_PIN_ALTERNATIVE;
	sda.output_type = SET_PIN_OPEN_DRAIN;
	sda.ouput_speed = SET_PIN_HSPEED;

	scl.port = GPIOB;
	scl.pin = 6;
	scl.Afmode = SET_PIN_AF4;
	scl.pull_up_down = SET_PIN_PULLUP;
	scl.mode = SET_PIN_ALTERNATIVE;
	scl.output_type = SET_PIN_OPEN_DRAIN;
	scl.ouput_speed = SET_PIN_HSPEED;

	i2c.I2C_Base = I2C1;
	i2c.I2C_Mode = I2C_SM_MODE;
	i2c.APB_PripheralFreq = 16;
	i2c.I2C_CCRValue = 0x50;
	i2c.I2C_TRISEValue = 17;

	GpioPinSet(sda);
	GpioPinSet(scl);
	I2C_Init(i2c);

	return 0;
}

int8_t setDate (uint8_t date, uint8_t mon, uint8_t year) {
	timedata.date = date;
	timedata.mon = mon;
	timedata.year = year;
	writeDatatoRTC(&timedata);
	return 0;
}


int8_t setTime (uint8_t hrs, uint8_t min, uint8_t sec) {
	timedata.hrs = hrs;
	timedata.min = min;
	timedata.sec = sec;
	writeDatatoRTC(&timedata);
	return 0;
}

int8_t getDataFromRTC (timeDate_t *data) {
	uint8_t tempBuffer[7];

	I2C_Start(I2C1, RTC_SLAVE_ADDRESS,I2C_WRITE_MODE);
	I2C_Write(I2C1, 0);
	I2C_Stop(I2C1);

	I2C_Start(I2C1, RTC_SLAVE_ADDRESS,I2C_READ_MODE);
	I2C_ReadContinoues(I2C1,0,tempBuffer,7);

//	printf("Time :: ");
//	for(int i = 0; i < 7;i++) {
//	printf("%d :",tempBuffer[i]);
//	}

//	printf("\n\n");
	data->sec = bcd2Decimal(tempBuffer[0]);
	data->min = bcd2Decimal(tempBuffer[1]);
	data->hrs = bcd2Decimal(tempBuffer[2]);
	data->date = bcd2Decimal(tempBuffer[4]);
	data->mon = bcd2Decimal(tempBuffer[5]);
	data->year = bcd2Decimal(tempBuffer[6]);

	//printf(" Time : %d : %d : %d   Date : %d / %d / %d\n",data->hrs,data->min,data->sec,data->date,data->mon,data->year);
	return 0;
}

int8_t writeDatatoRTC(timeDate_t *data) {
	I2C_Start(I2C1, RTC_SLAVE_ADDRESS,I2C_WRITE_MODE);
	I2C_Write(I2C1, 0);
	I2C_Write(I2C1, decimal2Bcd(data->sec));
	I2C_Write(I2C1, decimal2Bcd(data->min));
	I2C_Write(I2C1, decimal2Bcd(data->hrs));
	I2C_Write(I2C1, 1);
	I2C_Write(I2C1, decimal2Bcd(data->date));
	I2C_Write(I2C1, decimal2Bcd(data->mon));
	I2C_Write(I2C1, decimal2Bcd(data->year));
	I2C_Stop(I2C1);
	return 0;
}

int  bcd2Decimal(uint8_t to_convert)
{
	return (to_convert >> 4) * 10 + (to_convert & 0x0F);
}

int decimal2Bcd (int to_convert)
{
	return (uint8_t)( (to_convert/10*16) + (to_convert%10) );
}


void getTimeData(char *printBuffer) {
	getDataFromRTC(&timedata);
	sprintf(printBuffer,"\r\nTIME => %d::%d::%d \r\n",timedata.hrs,timedata.min,timedata.sec);
	printf("\rTime :: %s\n",printBuffer);
	xQueueSend(print_q,&printBuffer,portMAX_DELAY);
}

void getDateData(char *printBuffer) {
	getDataFromRTC(&timedata);
	sprintf(printBuffer,"\r\nDATE => %d/%d/%d \r\n",timedata.date,timedata.mon,timedata.year);
	printf("\rDate :: %s\n",printBuffer);
	xQueueSend(print_q,&printBuffer,portMAX_DELAY);
}


void timeCommandExtracter(command_t *cmd) {

	uint32_t hrs,min,sec = 0;
	if( cmd == NULL) {
		printf("Data was Not Received from the User \n");
		xQueueSend(print_q,&statusMenu[1],portMAX_DELAY);
		return;
	}

	if ( (cmd->playloadLength < 8) || (cmd->playloadLength > 8) ) {
		printf("Invalid Format Time \n");
		xQueueSend(print_q,&invalidMsg,portMAX_DELAY);
		return;
	}

	hrs = ( cmd->playload[0] * 10 )+(cmd->playload[1]);
	min = ( cmd->playload[3] * 10 )+(cmd->playload[4]);
	sec = ( cmd->playload[6] * 10 )+(cmd->playload[7]);


	setTime(hrs,min,sec);
	xQueueSend(print_q,&statusMenu[0],portMAX_DELAY);
	getTimeData(printBuffer);
}

void dateCommandExtracter(command_t *cmd) {
	uint32_t date,mon;
	uint32_t year;
	if( cmd == NULL) {
		printf("Data was Not Received from the User \n");
		xQueueSend(print_q,&statusMenu[1],portMAX_DELAY);
		return;
	}

	if ( (cmd->playloadLength < 8) || (cmd->playloadLength > 8) ) {
		printf("Invalid Format Time \n");
		xQueueSend(print_q,&invalidMsg,portMAX_DELAY);
		return;
	}

	date = ( cmd->playload[0] * 10 )+(cmd->playload[1]);
	mon = ( cmd->playload[3] * 10 )+(cmd->playload[4]);
	year = ( cmd->playload[6] * 10 )+(cmd->playload[7]);


	setDate(date,mon,year);
	xQueueSend(print_q,&statusMenu[0],portMAX_DELAY);
	getDateData(printBuffer);
}
