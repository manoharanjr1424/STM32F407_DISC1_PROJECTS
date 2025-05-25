/*
 * interrupt.c
 *
 *  Created on: Feb 23, 2025
 *      Author: mjayakumar
 */

#include <mcu.h>
#include <interrupt.h>

uint8_t NvicEnableInt(uint8_t IntNumber) {

	if( (IntNumber >=0) && (IntNumber < 32) ) {
		(*NVIC_ISER0) |= (1 << IntNumber);
	}
	else if( (IntNumber >= 32) && (IntNumber < 64) ) {
		(*NVIC_ISER1) |= (1 << (IntNumber%32));
	}else if( (IntNumber >= 64) && (IntNumber < 81) ) {
		(*NVIC_ISER2) |= (1 << (IntNumber%64));
	}

	return SUCCESS;
}

uint8_t NvicDisableInt(uint8_t IntNumber) {

	(*NVIC_ISER0) &= ~(1 << IntNumber);

	if( (IntNumber >=0) && (IntNumber < 32) ) {
		(*NVIC_ISER0) &= ~(1 << IntNumber);
	}
	else if( (IntNumber >= 32) && (IntNumber < 64) ) {
		(*NVIC_ISER1) &= ~(1 << (IntNumber%32));
	}else if( (IntNumber >= 64) && (IntNumber < 88) ) {
		(*NVIC_ISER2) &= ~(1 << (IntNumber%64));
	}
	return SUCCESS;
}

