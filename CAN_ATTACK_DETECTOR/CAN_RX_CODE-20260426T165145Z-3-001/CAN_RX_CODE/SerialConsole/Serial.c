/*
 * Serial.c
 *
 *  Created on: Apr 24, 2026
 *      Author: Windows
 */


#include "Serial.h"

extern UART_HandleTypeDef huart4;


void PrintLog(const char *str) {
	if ( HAL_UART_Transmit(&huart4,( const uint8_t *)str,strlen(str),1000) != HAL_OK) {
		printf("UART 4 Transmit Failed Check the Console Port \n");
		return;
	}
}
