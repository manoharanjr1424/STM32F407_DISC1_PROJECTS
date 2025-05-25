/*
 * i2c_header.h
 *
 *  Created on: Mar 25, 2025
 *      Author: mjayakumar
 */

#ifndef I2C_H_
#define I2C_H_

#include "mcu.h"

typedef enum {
	I2C_SM_MODE = 0,
	I2C_FM_MODE
}i2c_mode_t;

// Structure to handle I2C peripheral configuration and control
typedef struct {
    i2c_register_t *I2C_Base;       // Pointer to the base address of the I2C peripheral registers
    uint8_t I2C_Mode;               // I2C mode: Standard mode (100 kHz) or Fast mode (400 kHz)
    uint8_t APB_PripheralFreq;      // Frequency of the APB bus to which I2C is connected (in MHz)
    uint8_t I2C_Freq;               // Desired I2C communication frequency (in kHz)
    uint8_t I2C_CCRValue;           // Clock Control Register value to configure the I2C speed
    uint8_t I2C_TRISEValue;         // TRISE register value for maximum rise time configuration
} i2c_handler_t;



typedef enum {
	I2C_BUS_BUSY = 1,
	I2C_WRITE_FAILED,
	I2C_WRITE_SUCCESS
}i2c_response_t;



void I2C_Init(i2c_handler_t i2cHandle);
void I2C_Write(i2c_register_t *Base, uint8_t Data);
uint8_t I2C_WriteContinoues(i2c_register_t *Base, uint8_t Address,uint8_t Data, uint8_t len);
uint8_t I2C_Read(i2c_register_t *Base, uint8_t Address,uint8_t *Data);
uint8_t I2C_ReadContinoues(i2c_register_t *Base, uint8_t Address,uint8_t *Data);
uint8_t I2C_Start(i2c_register_t *Base, uint8_t slaveAddr);
uint8_t I2C_Stop(i2c_register_t *Base);


#endif /* I2C_H_ */
