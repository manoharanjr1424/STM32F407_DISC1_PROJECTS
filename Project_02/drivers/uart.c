/*
 * uart.c
 *
 *  Created on: Apr 25, 2025
 *      Author: mjayakumar
 */


#include "uart.h"

usartReturnStatus_t uartInit(usartHandle_t *uartData) {

	if ( uartPheripheralEnable((uint32_t *)uartData->usartBase) == USART_PHERIPHERAL_NOT_ENABLED) {
		return USART_INIT_FAILED;
	}




	uartCalculateBaurdRate(uartData);
	uartData->usartBase->CR1 &= ~(1 << 15);
	uartData->usartBase->CR1 |= (uartData->overSampling << 15);
	/*Uart WordLength set*/


	uartData->usartBase->CR1 &= ~(1 << 12);
	uartData->usartBase->CR1 |= (uartData->wordLength << 12);

	uartData->usartBase->CR1 |= (1 << 3);
	/*Uart Receiver Enable */
	uartData->usartBase->CR1 &= ~(1 << 2);
	uartData->usartBase->CR1 |= (1 << 2);
	/*Uart Oversampling Set*/


	usartEnable(uartData->usartBase);


	return USART_INIT_SUCCESSFULLY;
}


uint32_t uartWrite(usart_register_t *_Base,const char *string, size_t strlen) {
	uint32_t writtenCount = 0;
	while(writtenCount < strlen) {
		writtenCount++;
		uartSendChar(_Base, (char)string[writtenCount]);
	}
	return (writtenCount);
}

//Note : Not Implement Wet
uint32_t uartRead(usart_register_t *_Base,char *string) {
	return 0;
}

uint8_t uartSendChar(usart_register_t *_Base, char ch) {
	while(!( (_Base->SR) & (1 << 7) ) );
	_Base->DR = ch;
	while(!( (_Base->SR) & (1 << 6) ) );
	return 0;
}

uint8_t uartReceiveChar(usart_register_t *_Base) {
	while(! ( (_Base->SR) & (1 << 5) ));
	return (_Base->DR);
}

uint8_t uartPheripheralEnable(uint32_t  *Base) {
	if( Base == (uint32_t *)USART1 )	{ 	return (enableSysPheripheral(&(RCC->APB2ENR), ENABLE_USART1)); 	}
	else if( Base == (uint32_t *)USART2){ 	return (enableSysPheripheral(&(RCC->APB1ENR), ENABLE_USART2));	}
	else if( Base == (uint32_t *)USART3){	return (enableSysPheripheral(&(RCC->APB1ENR), ENABLE_USART3));	}
	else if( Base == (uint32_t *)UART4)	{	return (enableSysPheripheral(&(RCC->APB1ENR), ENABLE_UART4));	}
	else if( Base == (uint32_t *)UART5)	{	return (enableSysPheripheral(&(RCC->APB1ENR), ENABLE_UART5));	}
	else if( Base == (uint32_t *)USART6){	return (enableSysPheripheral(&(RCC->APB2ENR), ENABLE_USART6)); 	}
	else {return USART_PHERIPHERAL_NOT_ENABLED;}
	return 0;
}

usartReturnStatus_t enableSysPheripheral(volatile uint32_t *_Base, uint16_t Pos) {

	*(_Base) &= ~(1 << Pos);
	*(_Base) |= (1 << Pos);

	if( (*(_Base)) & (1 << Pos)) {
		return USART_PHERIPHERAL_ENABLED;
	} else {
		return USART_PHERIPHERAL_NOT_ENABLED;
	}
}



void uartCalculateBaurdRate(usartHandle_t *uartData) {

	uint16_t Mantissa = 0;
	uint8_t Fraction = 0;
	uint32_t clockFrequency = 0;
	 float usartdiv = 0.0;

	clockFrequency = GetSystemClockFrequency(APB1_SYSTEMBUS);

	if (uartData->overSampling == 1) // OVER8 = 1
	{
	    usartdiv = (float)clockFrequency / (8.0f * (float)uartData->baudRate);
	}
	else // OVER8 = 0
	{
	    usartdiv = (float)clockFrequency / (16.0f * (float)uartData->baudRate);
	}

	Mantissa = (uint16_t)usartdiv;


	Fraction = (uint8_t)( (usartdiv - (float)Mantissa) * (uartData->overSampling?(float)8.0:(float)16.0) + (float)0.5);

	if (uartData->overSampling == 1) {
	    Fraction &= 0x07; // Keep only 3 bits (bit 3 must be 0)
	} else {
	    Fraction &= 0x0F; // Keep all 4 bits
	}

	uartData->usartBase->BRR = (Mantissa << 4) | Fraction;
}

usartReturnStatus_t uartInterruptEnable(usart_register_t *Base,uint32_t InterruptType) {
//
//	Base->CR1 &= ~(1 << 8);
//	Base->CR1 |= (1 << 8);
//
//	if (!(Base->CR1 & (1 << 8))) {
//		return USART_INTERRUPT_NOT_ENABLED;
//	}

	if (InterruptType == TX_INTERRUPT) {
		Base->CR1 &= ~(1 << 7);
		Base->CR1 |= (1 << 7);

		if (!(Base->CR1 & (1 << 7))) {
			return USART_TX_INTERRUPT_NOT_ENABLED;
		} else {
			return USART_TX_INTERRUPT_ENABLED;
		}

	} else if (InterruptType == RX_INTERRUPT) {
		Base->CR1 &= ~(1 << 5);
		Base->CR1 |= (1 << 5);
		if (!(Base->CR1 & (1 << 5))) {
			return USART_RX_INTERRUPT_NOT_ENABLED;
		} else {
			return USART_RX_INTERRUPT_ENABLED;
		}
	}

	return USART_INTERRUPT_NOT_ENABLED;
}


usartReturnStatus_t uartInterruptDisable(usart_register_t *Base,uint32_t InterruptType) {

	if (InterruptType == TX_INTERRUPT) {
		Base->CR1 &= ~(1 << 7);

		if (!(Base->CR1 & (1 << 7))) {
			return USART_TX_INTERRUPT_DISABLED;
		} else {
			return USART_TX_INTERRUPT_NOT_DISABLED;
		}

	} else if (InterruptType == RX_INTERRUPT) {
		Base->CR1 &= ~(1 << 5);
		if (!(Base->CR1 & (1 << 5))) {
			return USART_RX_INTERRUPT_DISABLED;
		} else {
			return USART_RX_INTERRUPT_NOT_DISABLED;
		}
	}
	return USART_INTERRUPT_NOT_DISABLED;
}


uint8_t usartEnable(usart_register_t *_Base) {

	_Base->CR1 &= ~(1 << 13);
	_Base->CR1 |= (1 << 13);

	if (!(_Base->CR1) && (1 << 13)) {
		return 0;
	} else {
		return 1;
	}
}




