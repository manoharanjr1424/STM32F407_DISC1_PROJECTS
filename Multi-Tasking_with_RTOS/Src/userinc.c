#include "uartint.h"


uint8_t dummyData;
uint8_t user_data;


int32_t uartTOConsoleInit(void) {
	uartGpioInit();
	usartHandle_t uart;

	uart.baudRate = 9600;
	uart.usartBase = UART4;
	uart.overSampling = OVERSAMPLING_16;
	uart.parityBit = 0;
	uart.stopBit = STOP_BIT_0;
	uart.wordLength = 0;

	if ( uartInit(&uart) == USART_INIT_FAILED ) {
		printf(" UART Initialization was Failed \n");
		return -1;
	}
	printf(" UART Initialization was Completed \n");


	NvicSetPriorityGrouping(NVIC_PriorityGroup_4);
//	printf("UART 4 Priority %d\n",NvicGetPriority(UART4_IRQn));
	NvicSetPriority(UART4_IRQn,5,0);
	NvicEnableInt(UART4_IRQn);



	if (uartInterruptEnable(UART4, RX_INTERRUPT)
			== USART_RX_INTERRUPT_NOT_ENABLED) {
		printf("UART Interrupt was Not Enable\n");
		return -1;
	}

	printf("UART Interrupt was Enabled \n");
	return 0;
}

void uartGpioInit(void) {
	gpio_handler_t rx,tx;

	tx.mode = SET_PIN_ALTERNATIVE;
	rx.mode = SET_PIN_ALTERNATIVE;

	tx.pin = 10;
	rx.pin = 11;

	tx.Afmode = SET_PIN_AF8;
	rx.Afmode = SET_PIN_AF8;

	tx.port = GPIOC;
	rx.port = GPIOC;

	tx.pull_up_down = SET_PIN_NOPUPD;
	rx.pull_up_down = SET_PIN_NOPUPD;

	tx.output_type = 0;
	rx.output_type = 0;

	tx.ouput_speed = 0;
	rx.ouput_speed = 0;

	GpioPinSet(tx);
	GpioPinSet(rx);
}

void UART4_IRQHandler(void) {


	uartInterruptDisable(UART4,RX_INTERRUPT);
	while(! ( (UART4->SR) & (1 << 5)) );

	user_data = UART4->DR;

	printf("Received Data Was %c\n",user_data);

	if(xQueueIsQueueFullFromISR(data_q) != pdTRUE ) {
		/* QueueSendFromIsr was Insert the data into the tail of the
		 * Queue
		 */
		xQueueSendFromISR(data_q,&user_data,NULL);
		xTaskNotifyFromISR(cmdTask,0,eNoAction,NULL);

	} else {
		/* Here  i will check wheather Queue was Filled if user
		 * send the \n char then to delete one char from queue i use the
		 * read function read and insert the '\n' character to tail
		 */
		if(user_data == '\n' ) {
			xQueueReceiveFromISR(data_q, &dummyData, NULL);
			xQueueSendFromISR(data_q,&user_data, NULL);
			xTaskNotifyFromISR(cmdTask,0,eNoAction,NULL);
		}
	}
	uartInterruptEnable(UART4,RX_INTERRUPT);
}

