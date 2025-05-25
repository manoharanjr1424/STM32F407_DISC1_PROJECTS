/*
 * iocExpander.c
 *
 *  Created on: May 25, 2025
 *      Author: mjayakumar
 */

#include <ioExpander.h>




void ioExpanderPinInit(void) {
	gpio_handler_t sda,scl;

	sda.port = GPIOB;
	sda.pin = 7;
	sda.Afmode = SET_PIN_AF4;
	sda.pull_up_down = SET_PIN_PULLUP;
	sda.mode = SET_PIN_ALTERNATIVE;
	sda.output_type = SET_PIN_OPEN_DRAIN;
	sda.ouput_speed = SET_PIN_HSPEED;

	scl.port = GPIOB;
	scl.pin = 6;
	scl.Afmode = SET_PIN_AF4;
	scl.pull_up_down = SET_PIN_PULLUP;
	scl.mode = SET_PIN_ALTERNATIVE;
	scl.output_type = SET_PIN_OPEN_DRAIN;
	scl.ouput_speed = SET_PIN_HSPEED;

	GpioPinSet(sda);
	GpioPinSet(scl);
}



void ioExpanderwrite(i2c_register_t *const i2c_Base,uint8_t slaveAddr, uint8_t w_reg, uint8_t w_data) {
	I2C_Start(i2c_Base,slaveAddr);
	I2C_Write(i2c_Base,w_reg);
	I2C_Write(i2c_Base,w_data);
	I2C_Stop(i2c_Base);
}


void ioExpanderInit(void) {
	ioExpanderPinInit();

	i2c_handler_t i2c;

	i2c.I2C_Base = I2C1;
	i2c.I2C_Mode =I2C_SM_MODE;
	i2c.APB_PripheralFreq = 16;
	i2c.I2C_CCRValue = 0x50;
	i2c.I2C_TRISEValue = 17;

	I2C_Init(i2c);

}

