/*
 * timer.h
 *
 *  Created on: Mar 1, 2025
 *      Author: mjayakumar
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "mcu.h"

void TimerInit(tmr_9_register_t *Timer);
void TimerEnable(tmr_9_register_t *Timer, uint32_t PreLoad);
void TimerPrescaleSet(uint32_t ui32Base, uint32_t ui32preScaleValue);
void TimerDisable(tmr_9_register_t *Timer);
void TimerLoadValue(uint32_t ui32Base);
void MilliSecondsDelay(uint32_t delay);
void MicroSecondsDelay(uint32_t delay);
void SecondsDelay(uint32_t delay);
void delay_ms(uint32_t  delay_ms);

#endif /* TIMER_H_ */
