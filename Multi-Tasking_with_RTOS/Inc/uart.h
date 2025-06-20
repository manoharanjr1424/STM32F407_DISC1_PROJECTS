/*
 * uart.h
 *
 *  Created on: Apr 25, 2025
 *      Author: mjayakumar
 */

#ifndef UART_H_
#define UART_H_

#include "mcu.h"



typedef enum {
	STOP_BIT_0 = 0,
	STOP_BIT_05,
	STOP_BIT_2,
	STOP_BIT_15
}usartStopBitConfig_t;

typedef enum {
	CTS_ENABLE = 0,
	CTS_DISABLE,
	RTS_ENABLE,
	RTS_DISABLE,
	DMA_TRANSMITTER_ENBALE,
	DMA_TRANSMITTER_DISABLE,
	DMA_RECEIVER_ENBALE,
	DMA_RECEIVER_DISABLE,
	TX_INTERRUPT,
	RX_INTERRUPT
}usartGeneralConfig_t ;

typedef enum {
	USART_INIT_SUCCESSFULLY = 0,
	USART_INIT_FAILED,
	USART_PHERIPHERAL_DISABLED,
	USART_PHERIPHERAL_ENABLED,
	USART_PHERIPHERAL_NOT_ENABLED,
	USART_PHERIPHERAL_NOT_DISABLED,
	USART_INTERRUPT_ENABLED,
	USART_INTERRUPT_DISABLED,
	USART_INTERRUPT_NOT_ENABLED,
	USART_INTERRUPT_NOT_DISABLED,
	USART_TX_INTERRUPT_ENABLED,
	USART_TX_INTERRUPT_NOT_ENABLED,
	USART_TX_INTERRUPT_DISABLED,
	USART_TX_INTERRUPT_NOT_DISABLED,
	USART_RX_INTERRUPT_ENABLED,
	USART_RX_INTERRUPT_NOT_ENABLED,
	USART_RX_INTERRUPT_DISABLED,
	USART_RX_INTERRUPT_NOT_DISABLED
}usartReturnStatus_t;

typedef enum {
	OVERSAMPLING_16 = 0,
	OVERSAMPLING_8
}usartOversampling_t;

typedef enum {
	EVEN_PARITY = 0,
	ODD_PARITY
}usaetParityConfig_t;

typedef struct {
	usart_register_t *usartBase;
	uint32_t 	baudRate;
	uint8_t		stopBit;
	uint8_t 	overSampling;
	uint8_t 	parityBit;
	uint8_t		ctsEnable;
	uint8_t 	rtsEnable;
	uint8_t 	wordLength;
}usartHandle_t;


usartReturnStatus_t uartInit(usartHandle_t *);
uint32_t uartWrite(usart_register_t *_Base,const char *string, size_t strlen);
uint32_t uartRead(usart_register_t *,char *string);
uint8_t uartSendChar(usart_register_t *, char ch);
uint8_t uartReceiveChar(usart_register_t *);
uint8_t uartPheripheralEnable(uint32_t  *);
usartReturnStatus_t enableSysPheripheral(volatile uint32_t *, uint16_t);
void uartCalculateBaurdRate(usartHandle_t *);
usartReturnStatus_t uartInterruptEnable(usart_register_t *Base,uint32_t InterruptMode);
usartReturnStatus_t uartInterruptDisable(usart_register_t *Base,uint32_t InterruptType);
uint8_t usartEnable(usart_register_t *_Base);

#endif /* UART_H_ */
