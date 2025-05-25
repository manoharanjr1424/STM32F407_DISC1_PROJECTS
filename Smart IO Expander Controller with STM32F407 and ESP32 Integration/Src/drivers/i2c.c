
#include "i2c.h"
#include "timer.h"

void I2C_Init(i2c_handler_t i2cHandle) {

	if(i2cHandle.I2C_Base == I2C1) {
		RCC->APB1ENR |= (1 << 21);
	}else if(i2cHandle.I2C_Base == I2C2){
		RCC->APB1ENR |= (1 << 22);
	}else if(i2cHandle.I2C_Base == I2C3) {
		RCC->APB1ENR |= (1 << 23);
	}else {
		return;
	}

	i2cHandle.I2C_Base->I2C_CR1 |= (1 << 15);
	i2cHandle.I2C_Base->I2C_CR1 &= ~(1 << 15);

	i2cHandle.I2C_Base->I2C_CR1 &= ~(1 << 1);

	i2cHandle.I2C_Base->I2C_CR2 |= i2cHandle.APB_PripheralFreq; //16

	i2cHandle.I2C_Base->I2C_OAR1 |= (1 << 14);

	i2cHandle.I2C_Base->I2C_CCR |= i2cHandle.I2C_CCRValue;//0x50

	i2cHandle.I2C_Base->I2C_TRISE |= i2cHandle.I2C_TRISEValue;//17

	i2cHandle.I2C_Base->I2C_CR1 |= (1 << 0);
}

void I2C_Write(i2c_register_t *Base, uint8_t Data) {
	while(! (Base->I2C_SR1 & (1 << 7)) );
	Base->I2C_DR = Data;
	while(! (Base->I2C_SR1 & (1 << 7)) );
}
uint8_t I2C_WriteContinoues(i2c_register_t *Base, uint8_t Address, uint8_t Data, uint8_t len) {

	uint32_t ui32_LocalBaseloop = 0;
	while(!( (Base->I2C_SR1) & (1 << 7)) );
	Base->I2C_DR = (Address << 1);
	while((Base->I2C_SR1) & (1 << 1));

	for(ui32_LocalBaseloop = 0; ui32_LocalBaseloop < len; ui32_LocalBaseloop++) {
//		I2C_Start(Base);
		Base->I2C_DR = Data;
		while(!( (Base->I2C_SR1) & (1 << 7)) );
	}


}

uint8_t I2C_Read(i2c_register_t *Base, uint8_t Address, uint8_t *Data) {
	return 0;
}
uint8_t I2C_ReadContinoues(i2c_register_t *Base, uint8_t Address, uint8_t *Data){
	return 0;
}
uint8_t I2C_Start(i2c_register_t *Base, uint8_t slaveAddr) {

	uint32_t status_read;
	if((Base->I2C_SR2) & (1 << 1)) {
		return I2C_BUS_BUSY;
	}

	Base->I2C_CR1 |= (1 << 10);
	Base->I2C_CR1 |= (1 << 8);

	while(!((Base->I2C_SR1) & (1 << 0)));

	Base->I2C_DR = (slaveAddr << 1);

	MilliSecondsDelay(100);

	//while(!( Base->I2C_SR1 & 0x00000002) );


	status_read = ((Base->I2C_SR1)| (Base->I2C_SR2));

	return 0;
}

uint8_t I2C_Stop(i2c_register_t *Base) {

//	while(  ((Base->I2C_SR2) & (1 << 1)) );

	Base->I2C_CR1 |= (1 << 9);

	while(  ((Base->I2C_SR2) & (1 << 1)) );

	return 0;
}


