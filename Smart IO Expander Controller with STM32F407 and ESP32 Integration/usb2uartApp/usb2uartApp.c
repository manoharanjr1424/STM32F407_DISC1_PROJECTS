/*
 * usb2uartApp.c
 *
 *  Created on: May 25, 2025
 *      Author: mjayakumar
 */

#include <mcu.h>
#include <timer.h>
#include <gpio.h>
#include <i2c.h>
#include <uart.h>


#include "user.h"

static uint8_t serialInputBuffer[MAX_LEN];



uartSerialInputStatus_t status = {RX_DATA_READ_IDLE,0,RX_IDLE};

void update_Data_From_Appllication(void) {
	int32_t pinNumber = 0;
	uint8_t validPort = 0;
	if (status.data_read_status == RX_DATA_READY_TO_READ) {
		status.data_read_status = RX_DATA_READ_SUCCESSFULLY;
		if (stringValidation(((char *)serialInputBuffer), "IOEXP_PA", 8) == 0) {
			validPort = 1;
		} else if (stringValidation(((char *)serialInputBuffer), "IOEXP_PB", 8) == 0) {
			validPort = 2;
		} else {
			validPort = 0;
		}

		if (validPort > 0) {
			if (validPort == 1) {
				if ((pinNumber = arithmeticToNumeric((char *)(serialInputBuffer + 13)))
						>= 0) {

					if (stringValidation((char *)(serialInputBuffer + 15), "SET_INPUT",
							9) == 0) {
						switch (pinNumber) {

						case 0:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_0_DIR_INPUT);
							break;
						case 1:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_1_DIR_INPUT);
							break;
						case 2:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_2_DIR_INPUT);
							break;
						case 3:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_3_DIR_INPUT);
							break;
						case 4:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_4_DIR_INPUT);
							break;
						case 5:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_5_DIR_INPUT);
							break;
						case 6:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_6_DIR_INPUT);
							break;
						case 7:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_7_DIR_INPUT);
							break;
						}
					} else if (stringValidation((char *)(serialInputBuffer + 15),
							"SET_OUTPUT", 9) == 0) {
						switch (pinNumber) {
						case 0:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_0_DIR_OUTPUT);
							break;
						case 1:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_1_DIR_OUTPUT);
							break;
						case 2:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_2_DIR_OUTPUT);
							break;
						case 3:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_3_DIR_OUTPUT);
							break;
						case 4:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_4_DIR_OUTPUT);
							break;
						case 5:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_5_DIR_OUTPUT);
							break;
						case 6:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_6_DIR_OUTPUT);
							break;
						case 7:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRA,
									IO_PIN_7_DIR_OUTPUT);
							break;
						}
					} else if (stringValidation((char *)(serialInputBuffer + 15),
							"WRITE", 5) == 0) {
						switch (pinNumber) {
						case 0:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_LOW);
							}
							break;
						case 1:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_LOW);
							}
							break;
						case 2:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_LOW);
							}
							break;
						case 3:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_LOW);
							}
							break;
						case 4:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_LOW);
							}
							break;
						case 5:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_LOW);
							}
							break;
						case 6:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_LOW);
							}
							break;
						case 7:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOA,
										IO_PIN_0_LOW);
							}
							break;
						}
					} else if (stringValidation((char *)(serialInputBuffer + 15),
							"READ", 4) == 0) {

					}
				}
			} else if (validPort == 2) {
				if ((pinNumber = arithmeticToNumeric((char *)(serialInputBuffer + 13)))
						>= 0) {

					if (stringValidation((char *)(serialInputBuffer + 15), "SET_INPUT",
							9) == 0) {
						switch (pinNumber) {

						case 0:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_0_DIR_INPUT);
							break;
						case 1:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_1_DIR_INPUT);
							break;
						case 2:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_2_DIR_INPUT);
							break;
						case 3:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_3_DIR_INPUT);
							break;
						case 4:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_4_DIR_INPUT);
							break;
						case 5:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_5_DIR_INPUT);
							break;
						case 6:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_6_DIR_INPUT);
							break;
						case 7:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_7_DIR_INPUT);
							break;
						}
					} else if (stringValidation((char *)(serialInputBuffer + 15),
							"SET_OUTPUT", 9) == 0) {
						switch (pinNumber) {
						case 0:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_0_DIR_OUTPUT);
							break;
						case 1:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_1_DIR_OUTPUT);
							break;
						case 2:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_2_DIR_OUTPUT);
							break;
						case 3:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_3_DIR_OUTPUT);
							break;
						case 4:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_4_DIR_OUTPUT);
							break;
						case 5:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_5_DIR_OUTPUT);
							break;
						case 6:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_6_DIR_OUTPUT);
							break;
						case 7:
							ioExpanderwrite(I2C1, 0x20, MCP23017_IODIRB,
									IO_PIN_7_DIR_OUTPUT);
							break;
						}
					} else if (stringValidation((char *)(serialInputBuffer + 15),
							"WRITE", 5) == 0) {
						switch (pinNumber) {
						case 0:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_LOW);
							}
							break;
						case 1:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_LOW);
							}
							break;
						case 2:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_LOW);
							}
							break;
						case 3:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_LOW);
							}
							break;
						case 4:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_LOW);
							}
							break;
						case 5:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_LOW);
							}
							break;
						case 6:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_LOW);
							}
							break;
						case 7:
							if (stringValidation((char *)(serialInputBuffer + 21),
									"HIGH", 4) == 0) {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_HIGH);
							} else {
								ioExpanderwrite(I2C1, 0x20, MCP23017_GPIOB,
										IO_PIN_0_LOW);
							}
							break;
						}
					} else if (stringValidation((char *)(serialInputBuffer + 15),
							"READ", 4) == 0) {

					}
				}

			}
		}
	}

}



void updateSerialInputBuffer(const uint8_t chr) {
	if(chr == START_BYTE) {
		status.rx_status = RX_ONGOING;
		status.rx_data_length = 0;
	}else if(chr == STOP_BYTE) {
		serialInputBuffer[status.rx_data_length] = '\0';
		status.rx_status = RX_COMPLETED;
		status.data_read_status = RX_DATA_READY_TO_READ;

	}else if(status.rx_status == RX_ONGOING) {
		serialInputBuffer[status.rx_data_length] = chr;
		status.rx_data_length++;
	}
}


void uartPinInit(void) {


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


void userApplicationInit(void) {
	uartPinInit();
	usartHandle_t uart;

	uart.baudRate = 9600;
	uart.usartBase = UART4;
	uart.overSampling = OVERSAMPLING_16;
	uart.parityBit = 0;
	uart.stopBit = STOP_BIT_0;
	uart.wordLength = 0;

	uartInit(&uart);
	NvicEnableInt(UART4_IRQn);

	if (uartInterruptEnable(UART4, RX_INTERRUPT)
			== USART_RX_INTERRUPT_NOT_ENABLED) {
		printf("uart Interrupt was Not Enable\n");
	}

}


void UART4_IRQHandler(void) {

	uartInterruptDisable(UART4,RX_INTERRUPT);
	while(! ( (UART4->SR) & (1 << 5)) );
	updateSerialInputBuffer(UART4->DR);
	uartInterruptEnable(UART4,RX_INTERRUPT);
}


uint8_t stringCompare(uint8_t *src, uint8_t *des) {
	uint32_t index  = 0;
	for( ;src[index]!='\0';index++){
		if( src[index] != des[index]) {
			return 1;
		}
	}

	return 0;
}

int32_t arithmeticToNumeric(char *chr) {
	int32_t value;

	value = ((*chr) - '0');
	if ( (value >= 0) && ( value < 8)) {
		return value;
	}

	return(-1);
}

uint8_t stringValidation(char *src, char *des, uint32_t len) {
	uint32_t Index = 0;

	for( ;Index < len; Index++) {
		if(src[Index] != des[Index]) {
			return 1;
		}
	}
	return 0;
}

