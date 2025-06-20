#include "cmd.h"

char   *invalidMsg = "\n ================================= \n INVALID OPTION \n ================================= \n";


int32_t processCommand(command_t *cmd) {
	ExtractCommand(cmd);

	printf("Command was Extracted Successfully and notified to the user \n");

	if (cmd->playloadLength < 1) {
		printf("invalid payload \n");
		return -1;
	}

	switch (currentState) {
	case sMainMenu:
		printf(" Notifying to MainMenu task to print menu \n");
		xTaskNotify(menuTask,(uint32_t)cmd,eSetValueWithOverwrite);
		break;
	case sLedEffect:
		printf(" Notifying to Led task to print led menu \n");
		xTaskNotify(ledTask,(uint32_t)cmd,eSetValueWithOverwrite);
		break;
	case sRtcMenu:
		printf(" Notifying to RTC task to print menu \n");
		xTaskNotify(rtcTask,(uint32_t)cmd,eSetValueWithOverwrite);
		break;
	}

	return 0;
}

int32_t ExtractCommand(command_t *cmd) {
	uint32_t index = 0;
	uint8_t queueData;
	BaseType_t retStatus;

	retStatus = uxQueueMessagesWaiting(data_q);

	if (retStatus != pdFAIL) {

		do {
			retStatus = xQueueReceive(data_q, &queueData, portMAX_DELAY);
			if( retStatus == pdFAIL) {
				printf(" Receiving From the Queue was Failed \n");
				return -1;
			}
			cmd->playload[index++] = queueData - 48;
		}while(queueData != '\n');


	} else {

		printf("No Data in the Data Queue Verify Data was Pushed into the Queue\n");
		return -1;
	}

	cmd->playload[index - 1] = '\0';
	cmd->playloadLength = (index - 1);
	printf("Successfully Playload  was Extracted from the Queue\n");

	//xTaskNotify(menuTask,(uint32_t *)&cmd,eSetValueWithOverwrite);

	return 0;
}
