#include "main.h"
#include "uartint.h"
#include "led.h"
#include "mainmenu.h"
#include "cmd.h"
#include "rtc.h"
#include "mainmenu.h"



uint32_t SystemCoreClock = 16000000;




QueueHandle_t data_q;
QueueHandle_t print_q;
TimerHandle_t timerHandle[4];

/* Task Handle for the Each separate Task . TaskHandle_t
 * was nothing information about the  task using the
 * this handle_t we can point out the task
 */

TaskHandle_t menuTask;
TaskHandle_t cmdTask;
TaskHandle_t ledTask;
TaskHandle_t uartTask;
TaskHandle_t rtcTask;


//char printDataToConsole[1024] = {0};
char *printDataToConsole;
char invalid_option[50] = "\n\\\\\ INVALID OPTION /////\n\r";
timeDate_t timedata;

state_t currentState = sMainMenu;

int main(void) {

	BaseType_t retStatus;

	ENABLE_FPU();
	TimerInit(TIMER9);
	uartTOConsoleInit();
	initInbuildLed();
	RTCInit();
	if ( initialize_SoftwareTimer(timerHandle) != 0 ) {
		printf("Timer Initialized Failed \n");
		return -1;
	}
	printf("General Purpose Peripheral Was Enabled and Initialized \n");

	data_q = xQueueCreate(20,sizeof(char *));
	if( data_q == NULL ) {
		printf("ERROR :: Insufficient Heap Memory Data Queue Was Not Created \n");
		return -1;
	}

	print_q = xQueueCreate(20,sizeof(char *));
	if( print_q == NULL) {
		printf("ERROR :: Insufficient Heap Memory Print Queue Was Not Created \n");
		return -1;
	}

	printf("Queue for Data and Print to the UART to USER was Created Successfully\r\n");


	retStatus = xTaskCreate(func_MainMenuTask, "Main Menu", 300, NULL, 3, &menuTask);
	configASSERT(retStatus == pdPASS);

	retStatus = xTaskCreate(func_UartConsoleTask, "UART Console", 300, NULL, 3, &uartTask);
	configASSERT(retStatus == pdPASS);

	retStatus = xTaskCreate(func_LedEffectTask, "Led Effects", 300, NULL, 3, &ledTask);
	configASSERT(retStatus == pdPASS);

	retStatus = xTaskCreate(func_RtcTask, "RTC Task", 300, NULL, 3, &rtcTask);
	configASSERT(retStatus == pdPASS);

	retStatus = xTaskCreate(func_CmdParsingTask, "CMD Task", 300, NULL, 3, &cmdTask);
	configASSERT(retStatus == pdPASS);
	vTaskStartScheduler();

	return 0;
}


void func_MainMenuTask(void *pvParameters) {
	mainMenu();
}

void func_UartConsoleTask(void *pvParameters) {
	BaseType_t retStatus;

	printf("Waiting for User to Enter the Data \n");
	while (1) {

		retStatus = uxQueueMessagesWaiting(print_q);

		if (retStatus == pdPASS) {
			retStatus = xQueueReceive(print_q,&printDataToConsole,portMAX_DELAY);
			if (retStatus == pdFAIL) {

				printf("Queue not received any data \n");

			} else {

				printf("Data to Print %s \n", printDataToConsole);
				uartWrite(UART4, printDataToConsole,strlen(printDataToConsole));
				printf("Print Data buffer was flushed \n");

			}
		}
	}
}


void func_LedEffectTask(void *pvParameters) {
	command_t cmd;
	while(1) {
		ledPatternPrint(&cmd);
	}
}

void func_RtcTask(void *pvParameters) {


	timedata.date = 19;
	timedata.mon = 6;
	timedata.year = 24;
	timedata.sec = 50;
	timedata.min = 59;
	timedata.hrs = 23;
//	writeDatatoRTC(&timedata);
	while(1) {
		RTCMenu();
//		getDataFromRTC(&timedata);
//		vTaskDelay(1000);
	}
}

void func_CmdParsingTask(void *pvParameters) {
	BaseType_t retStatus;
	command_t cmd;

	while(1) {
		xTaskNotifyStateClear(NULL);
		retStatus = xTaskNotifyWait(0,0,NULL, portMAX_DELAY);

		if( retStatus == pdPASS) {
			processCommand(&cmd);
		} else {
			printf("Notification failed send by the Uart \n");
		}
	}
}


int8_t initialize_SoftwareTimer(TimerHandle_t *timer) {
	uint8_t i = 0;

	for( ; i < 4; i++) {
		timer[i] = xTimerCreate("softwareTimer", pdMS_TO_TICKS(500), pdTRUE, (void *)(i +1),softwareTimerCallback);
	}

	for( i = 0; i < 4; i++) {
		if( timer[i] == NULL) {
			return -1;
		}
	}
	return 0;
}




