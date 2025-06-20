/*
 * led.c
 *
 *  Created on: Jun 5, 2025
 *      Author: mjayakumar
 */

#include "led.h"

char *ledMenu = "\r\r\r\r\n========= LED MENU =========== \r\r\r\n [1] LED Effect 1\r\n\n\r[2] LED Effect 2\r\n\n\r[3] LED Effect 3\n\r\n\r[4] LED Effect 4\n\r\n\r[5] Back to Menu \n\rEnter Choice : ";


void initInbuildLed(void){
	gpio_handler_t led1,led2,led3,led4;

	led1.pin = 12;
	led1.port = GPIOD;
	led1.mode = SET_PIN_OUTPUT;
	led1.ouput_speed = SET_PIN_LSPEED;
	led1.output_type = SET_PIN_PUSH_PULL;
	led1.pull_up_down = SET_PIN_NOPUPD;

	led2.pin = 13;
	led2.port = GPIOD;
	led2.mode = SET_PIN_OUTPUT;
	led2.ouput_speed = SET_PIN_LSPEED;
	led2.output_type = SET_PIN_PUSH_PULL;
	led2.pull_up_down = SET_PIN_NOPUPD;


	led3.pin = 14;
	led3.port = GPIOD;
	led3.mode = SET_PIN_OUTPUT;
	led3.ouput_speed = SET_PIN_LSPEED;
	led3.output_type = SET_PIN_PUSH_PULL;
	led3.pull_up_down = SET_PIN_NOPUPD;


	led4.pin = 15;
	led4.port = GPIOD;
	led4.mode = SET_PIN_OUTPUT;
	led4.ouput_speed = SET_PIN_LSPEED;
	led4.output_type = SET_PIN_PUSH_PULL;
	led4.pull_up_down = SET_PIN_NOPUPD;

	GpioPinSet(led1);
	GpioPinSet(led2);
	GpioPinSet(led3);
	GpioPinSet(led4);

	printf(" Gpio Pin From PORTD Inbuilt led  Initialized \n");
}


void ledPatternPrint(command_t *cmd) {


	BaseType_t retStatus;
	uint32_t cmd_addr;
	uint8_t option;


	xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
	xTaskNotifyStateClear(NULL);

	xQueueReset(print_q);
	retStatus = xQueueSend(print_q,&ledMenu,portMAX_DELAY);

	if( retStatus == pdFAIL) {
		printf("\n Led Menu print was Failed \n");
		return;
	}


	xTaskNotifyWait(0,0,&cmd_addr,portMAX_DELAY);
	xTaskNotifyStateClear(NULL);

	cmd = (command_t *)cmd_addr;

	option = cmd->playload[0];

	if(option == 0){
		printf("Invalid Option \n");
		xQueueSend(print_q,invalid_option,portMAX_DELAY);
		currentState = sMainMenu;
		xTaskNotify(menuTask,0,eNoAction);
		return;
	}

	switch(option){
	case 1:
		startSoftwareTimer(1);
		break;
	case 2:
		startSoftwareTimer(2);
		break;
	case 3:
		startSoftwareTimer(3);
		break;
	case 4:
		startSoftwareTimer(4);
		break;
	}

	xTaskNotify(menuTask,0,eNoAction);
	currentState = sMainMenu;
}


void softwareTimerCallback(TimerHandle_t timer) {

	int id = (int)pvTimerGetTimerID(timer);
	switch(id) {
	case 1:
		led_effect_one();
		break;
	case 2:
		led_effect_two();
		break;
	case 3:
		led_effect_three();
		break;
	case 4:
		led_effect_four();
		break;
	}
}

void stopSoftwareTimer(void) {

	for(uint8_t i = 0; i < 4; i++) {
		if(timerHandle[i] == NULL) {
			printf("Timer was Not Initialized \n");
			continue;
		}
		xTimerStop(timerHandle[i],portMAX_DELAY);
	}
}

void startSoftwareTimer(uint8_t n) {
	stopSoftwareTimer();
	xTimerStart(timerHandle[n-1],portMAX_DELAY);
}

void led_effect_one(void) {
	static uint8_t previous_state = 1;

	GpioPinWrite(GPIOD, 12, previous_state);
	GpioPinWrite(GPIOD, 13, previous_state);
	GpioPinWrite(GPIOD, 14, previous_state);
	GpioPinWrite(GPIOD, 15, previous_state);

	previous_state ^= 1;

}
void led_effect_two(void){

	static uint8_t previous_odd_state = 1;

	if( previous_odd_state) {
		GpioPinWrite(GPIOD, 12, LOW);
		GpioPinWrite(GPIOD, 13, HIGH);
		GpioPinWrite(GPIOD, 14, LOW);
		GpioPinWrite(GPIOD, 15, HIGH);
	} else {
		GpioPinWrite(GPIOD, 12, HIGH);
		GpioPinWrite(GPIOD, 13, LOW);
		GpioPinWrite(GPIOD, 14, HIGH);
		GpioPinWrite(GPIOD, 15, LOW);
	}

	previous_odd_state ^= 1;
}


void led_effect_three(void){
	static uint8_t effectThreeLoopCount = 12;
	led_off_all();
	GpioPinWrite(GPIOD, effectThreeLoopCount, HIGH);
	effectThreeLoopCount++;
	if(effectThreeLoopCount > 16) {
		effectThreeLoopCount = 12;
	}
}

void led_effect_four(void){
	static uint8_t effectFourLoopCount = 16;
	led_off_all();
	GpioPinWrite(GPIOD, effectFourLoopCount, HIGH);
	effectFourLoopCount--;
	if (effectFourLoopCount < 12) {
		effectFourLoopCount = 16;
	}
}


void led_off_all(void) {
	GpioPinWrite(GPIOD, 12, LOW);
	GpioPinWrite(GPIOD, 13, LOW);
	GpioPinWrite(GPIOD, 14, LOW);
	GpioPinWrite(GPIOD, 15, LOW);
}

