/*
 * Serial.c
 *
 *  Created on: Apr 24, 2026
 *      Author: Windows
 */


#include "Serial.h"

extern UART_HandleTypeDef huart4;

static unsigned char UserInput[3];
volatile static uint8_t ReadToUse = 0;

unsigned char menu[] = {"\r\n ================[ MAIN MENU ]================= \n\r"
						  "Press [1] Unauthrozied Attack \r\n"
						  "Press [2] Replay Attack \r\n"
						  "Press [3] Spoofing Attack \r\n"
						  "Press [4] Flooding/DOS Attack\r\n"
						  "Press [5] Normal Message\r\n"
					      "Enter the Choice :: "};


void MainMenu (void) {


	uint8_t userChoice = 0;

	 HAL_UART_Receive_IT(&huart4, UserInput, 1);
	if ( HAL_UART_Transmit(&huart4, menu, sizeof(menu), 1000) != HAL_OK ) {
		printf("Error in uart Transmitting \n");
		return;
	}

	while(!ReadToUse);

	ReadToUse = 0;

	userChoice = atoi((const char *)UserInput);

	switch(userChoice) {
	case UNAUTHRIZED_ATTACK:
		PrintLog("\r\n UNAUTHRIZED ATTCAK STARTING \n");
		PrintLog("\r\n UNAUTHRIZED ATTACK STARTED PRESS x or X to stop  \r\n");
		UnauthorizedAttack();
		break;
	case REPLAY_ATTACK:
		PrintLog("\r\n REPLAY ATTCAK STARTING \n");
		PrintLog("\r\n REPLAY ATTACK STARTED PRESS x or X to stop  \r\n");
		ReplayAttack();
		break;
	case SPOOFING_ATATCK:
		PrintLog("\r\n SPOOFING ATTCAK STARTING \n");
		PrintLog("\r\n SPOOFING ATTACK STARTED PRESS x or X to stop  \r\n");
		SpoofingAttack();
		break;
	case FLOODING_ATTACK:
		PrintLog("\r\n FLOODING ATTCAK STARTING \n");
		PrintLog("\r\n FLOODING ATTACK STARTED PRESS x or X to stop  \r\n");
		FloodingAttack();
		break;
	case NORMAL_MESSAGE:
		NormalMessage();
		PrintLog("\r\n NORMAL MESSAGE STARTING \n");
		PrintLog("\r\n NORMAL MESSAGE STARTED PRESS x or X to stop  \r\n");
		break;
	default:
		printf("Invalid Option\n");
		PrintLog( "\r\n Invalid Option \r\n");
		PrintLog((const char *)menu);
	}
}

uint8_t ReadExitStatus (void ) {
	if(ReadToUse){
		ReadToUse = 0;
		if((UserInput[0] =='x') || (UserInput[0] =='X') ) {
			return 1;
		}
	}

	return 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	ReadToUse = 1;
	HAL_UART_Receive_IT(&huart4, UserInput, 1);
}


void PrintLog(const char *str) {
	if ( HAL_UART_Transmit(&huart4,( const uint8_t *)str,strlen(str),1000) != HAL_OK) {
		printf("UART 4 Transmit Failed Check the Console Port \n");
		return;
	}
}
