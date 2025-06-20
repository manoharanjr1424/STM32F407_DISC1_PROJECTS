/*
 * main.h
 *
 *  Created on: Jun 5, 2025
 *      Author: mjayakumar
 */

#ifndef MAIN_H_
#define MAIN_H_


#include "mcu.h"
#include "timer.h"
#include "gpio.h"
#include "i2c.h"
#include "uart.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "portable.h"
#include "timers.h"
#include "portmacro.h"




typedef enum {
	sMainMenu =0,
	sLedEffect,
	sRtcMenu,
	sRtcTimeConfig,
	sRtcDateConfig,
	sRtcReport,
}state_t;


typedef struct {
	uint8_t playload[10];
	uint32_t playloadLength;
}command_t;


extern QueueHandle_t data_q;
extern QueueHandle_t print_q;

/* Task Handle for the Each separate Task . TaskHandle_t
 * was nothing information about the  task using the
 * this handle_t we can point out the task
 */


extern TaskHandle_t menuTask;
extern TaskHandle_t cmdTask;
extern TaskHandle_t ledTask;
extern TaskHandle_t uartTask;
extern TaskHandle_t rtcTask;


extern state_t currentState;
extern TimerHandle_t timerHandle[4];

void func_MainMenuTask(void *parameters);
void func_UartConsoleTask(void *parameters);
void func_LedEffectTask(void *pvParameters);
void func_RtcTask(void *pvParameters);
void func_CmdParsingTask(void *pvParameters);
int8_t initialize_SoftwareTimer(TimerHandle_t *);
void softwareTimerCallback(TimerHandle_t );




extern char invalid_option[50];
extern char   *invalidMsg;





#endif /* MAIN_H_ */
