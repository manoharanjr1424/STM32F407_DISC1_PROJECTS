/*
 * user.h
 *
 *  Created on: May 25, 2025
 *      Author: mjayakumar
 */

#ifndef USER_H_
#define USER_H_

#include "ioExpander.h"


#define MAX_LEN 200

#define START_BYTE         0x81   // Extended ASCII � �
#define STOP_BYTE          0xA5   // Extended ASCII � � (Yen sign)

#define SSL_BYTE_3         0xC7   // Extended ASCII � � (Latin capital letter C with cedilla)
#define SSL_BYTE_4         0xF0   // Extended ASCII � � (Latin small letter eth)



typedef enum {
	RX_IDLE = 0,
	RX_COMPLETED,
	RX_ONGOING,
	RX_FAILED,
	RX_TIMEOUT
}uartRxStatus_t;


typedef enum {
	RX_DATA_READ_SUCCESSFULLY = 0,
	RX_DATA_READ_FAILED,
	RX_DATA_READY_TO_READ,
	RX_DATA_READ_IDLE
}uartDataRead_t;

typedef struct {
	uartDataRead_t data_read_status;
	uint32_t rx_data_length;
	uartRxStatus_t rx_status;
}uartSerialInputStatus_t;


//struct ioExpanderData{
//	uint8_t GPIO_ADDR;
//	uint8_t GPIO_PIN_STATE[20];
//	uint8_t GPIO_PIN_DATA[20];
//}ioExpanderData_t;

void updateSerialInputBuffer(const uint8_t chr);
void userApplicationInit(void);
void update_Data_From_Appllication(void);
void uartPinInit(void);
void UART4_IRQHandler(void);
uint8_t stringCompare(uint8_t *, uint8_t *);
int32_t arithmeticToNumeric(char *chr);
uint8_t stringValidation(char *, char *, uint32_t);
#endif /* USER_H_ */
