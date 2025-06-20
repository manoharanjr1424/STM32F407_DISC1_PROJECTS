/*
 * uartint.h
 *
 *  Created on: Jun 5, 2025
 *      Author: mjayakumar
 */

#ifndef UARTINT_H_
#define UARTINT_H_

#include "main.h"

int32_t uartTOConsoleInit(void);
void uartGpioInit(void);
void UART4_IRQHandler(void);
#endif /* UARTINT_H_ */
