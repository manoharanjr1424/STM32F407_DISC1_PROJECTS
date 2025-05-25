/*
 * ioExpander.h
 *
 *  Created on: May 25, 2025
 *      Author: mjayakumar
 */

#ifndef IOEXPANDER_H_
#define IOEXPANDER_H_

#include <mcu.h>
#include <timer.h>
#include <gpio.h>
#include <i2c.h>
#include <uart.h>
#include <user.h>

#define MCP23017_SLAVE_ADDR 0x20


// MCP23017 Register Address Macros
#define MCP23017_IODIRA     0x00  // I/O direction register A
#define MCP23017_IODIRB     0x01  // I/O direction register B
#define MCP23017_IPOLA      0x02  // Input polarity register A
#define MCP23017_IPOLB      0x03  // Input polarity register B
#define MCP23017_GPINTENA   0x04  // Interrupt-on-change control register A
#define MCP23017_GPINTENB   0x05  // Interrupt-on-change control register B
#define MCP23017_DEFVALA    0x06  // Default compare register for interrupt-on-change A
#define MCP23017_DEFVALB    0x07  // Default compare register for interrupt-on-change B
#define MCP23017_INTCONA    0x08  // Interrupt control register A
#define MCP23017_INTCONB    0x09  // Interrupt control register B
#define MCP23017_IOCON      0x0A  // I/O Expander configuration register
#define MCP23017_IOCON_ALT  0x0B  // Alternate address for IOCON (both point to same register)
#define MCP23017_GPPUA      0x0C  // Pull-up resistor configuration register A
#define MCP23017_GPPUB      0x0D  // Pull-up resistor configuration register B
#define MCP23017_INTFA      0x0E  // Interrupt flag register A
#define MCP23017_INTFB      0x0F  // Interrupt flag register B
#define MCP23017_INTCAPA    0x10  // Interrupt captured value for port A
#define MCP23017_INTCAPB    0x11  // Interrupt captured value for port B
#define MCP23017_GPIOA      0x12  // General purpose I/O port A
#define MCP23017_GPIOB      0x13  // General purpose I/O port B
#define MCP23017_OLATA      0x14  // Output latch register 0 (A)
#define MCP23017_OLATB      0x15  // Output latch register 1 (B)


// Direction Macros
#define IO_PIN_0_DIR_INPUT     0x01
#define IO_PIN_1_DIR_INPUT     0x02
#define IO_PIN_2_DIR_INPUT     0x03
#define IO_PIN_3_DIR_INPUT     0x04
#define IO_PIN_4_DIR_INPUT     0x05
#define IO_PIN_5_DIR_INPUT     0x06
#define IO_PIN_6_DIR_INPUT     0x07
#define IO_PIN_7_DIR_INPUT     0x08

#define IO_PIN_0_DIR_OUTPUT    0x00
#define IO_PIN_1_DIR_OUTPUT    0x00
#define IO_PIN_2_DIR_OUTPUT    0x00
#define IO_PIN_3_DIR_OUTPUT    0x00
#define IO_PIN_4_DIR_OUTPUT    0x00
#define IO_PIN_5_DIR_OUTPUT    0x00
#define IO_PIN_6_DIR_OUTPUT    0x00
#define IO_PIN_7_DIR_OUTPUT    0x00

// State Macros
#define IO_PIN_0_LOW           0x00
#define IO_PIN_1_LOW           0x00
#define IO_PIN_2_LOW           0x00
#define IO_PIN_3_LOW           0x00
#define IO_PIN_4_LOW           0x00
#define IO_PIN_5_LOW           0x00
#define IO_PIN_6_LOW           0x00
#define IO_PIN_7_LOW           0x00

#define IO_PIN_0_HIGH          0x01
#define IO_PIN_1_HIGH          0x02
#define IO_PIN_2_HIGH          0x03
#define IO_PIN_3_HIGH          0x04
#define IO_PIN_4_HIGH          0x05
#define IO_PIN_5_HIGH          0x06
#define IO_PIN_6_HIGH          0x07
#define IO_PIN_7_HIGH          0x08





// IO Expander Port A - Pin 0 operations
#define IO_EXP_A_PIN_00_SET_INPUT     "IOEXP_PA_PIN00_SET_INPUT"
#define IO_EXP_A_PIN_00_SET_OUTPUT    "IOEXP_PA_PIN00_SET_OUTPUT"
#define IO_EXP_A_PIN_00_WRITE_HIGH    "IOEXP_PA_PIN00_WRITE_HIGH"
#define IO_EXP_A_PIN_00_WRITE_LOW     "IOEXP_PA_PIN00_WRITE_LOW"

// IO Expander Port A - Pin 1 operations
#define IO_EXP_A_PIN_01_SET_INPUT     "IOEXP_PA_PIN01_SET_INPUT"
#define IO_EXP_A_PIN_01_SET_OUTPUT    "IOEXP_PA_PIN01_SET_OUTPUT"
#define IO_EXP_A_PIN_01_WRITE_HIGH    "IOEXP_PA_PIN01_WRITE_HIGH"
#define IO_EXP_A_PIN_01_WRITE_LOW     "IOEXP_PA_PIN01_WRITE_LOW"

// IO Expander Port A - Pin 2 operations
#define IO_EXP_A_PIN_02_SET_INPUT     "IOEXP_PA_PIN02_SET_INPUT"
#define IO_EXP_A_PIN_02_SET_OUTPUT    "IOEXP_PA_PIN02_SET_OUTPUT"
#define IO_EXP_A_PIN_02_WRITE_HIGH    "IOEXP_PA_PIN02_WRITE_HIGH"
#define IO_EXP_A_PIN_02_WRITE_LOW     "IOEXP_PA_PIN02_WRITE_LOW"

// IO Expander Port A - Pin 3 operations
#define IO_EXP_A_PIN_03_SET_INPUT     "IOEXP_PA_PIN03_SET_INPUT"
#define IO_EXP_A_PIN_03_SET_OUTPUT    "IOEXP_PA_PIN03_SET_OUTPUT"
#define IO_EXP_A_PIN_03_WRITE_HIGH    "IOEXP_PA_PIN03_WRITE_HIGH"
#define IO_EXP_A_PIN_03_WRITE_LOW     "IOEXP_PA_PIN03_WRITE_LOW"

// IO Expander Port A - Pin 4 operations
#define IO_EXP_A_PIN_04_SET_INPUT     "IOEXP_PA_PIN04_SET_INPUT"
#define IO_EXP_A_PIN_04_SET_OUTPUT    "IOEXP_PA_PIN04_SET_OUTPUT"
#define IO_EXP_A_PIN_04_WRITE_HIGH    "IOEXP_PA_PIN04_WRITE_HIGH"
#define IO_EXP_A_PIN_04_WRITE_LOW     "IOEXP_PA_PIN04_WRITE_LOW"

// IO Expander Port A - Pin 5 operations
#define IO_EXP_A_PIN_05_SET_INPUT     "IOEXP_PA_PIN05_SET_INPUT"
#define IO_EXP_A_PIN_05_SET_OUTPUT    "IOEXP_PA_PIN05_SET_OUTPUT"
#define IO_EXP_A_PIN_05_WRITE_HIGH    "IOEXP_PA_PIN05_WRITE_HIGH"
#define IO_EXP_A_PIN_05_WRITE_LOW     "IOEXP_PA_PIN05_WRITE_LOW"

// IO Expander Port A - Pin 6 operations
#define IO_EXP_A_PIN_06_SET_INPUT     "IOEXP_PA_PIN06_SET_INPUT"
#define IO_EXP_A_PIN_06_SET_OUTPUT    "IOEXP_PA_PIN06_SET_OUTPUT"
#define IO_EXP_A_PIN_06_WRITE_HIGH    "IOEXP_PA_PIN06_WRITE_HIGH"
#define IO_EXP_A_PIN_06_WRITE_LOW     "IOEXP_PA_PIN06_WRITE_LOW"

// IO Expander Port A - Pin 7 operations
#define IO_EXP_A_PIN_07_SET_INPUT     "IOEXP_PA_PIN07_SET_INPUT"
#define IO_EXP_A_PIN_07_SET_OUTPUT    "IOEXP_PA_PIN07_SET_OUTPUT"
#define IO_EXP_A_PIN_07_WRITE_HIGH    "IOEXP_PA_PIN07_WRITE_HIGH"
#define IO_EXP_A_PIN_07_WRITE_LOW     "IOEXP_PA_PIN07_WRITE_LOW"


// IO Expander Port B - Pin 0 operations
#define IO_EXP_B_PIN_00_SET_INPUT     "IOEXP_PB_PIN00_SET_INPUT"
#define IO_EXP_B_PIN_00_SET_OUTPUT    "IOEXP_PB_PIN00_SET_OUTPUT"
#define IO_EXP_B_PIN_00_WRITE_HIGH    "IOEXP_PB_PIN00_WRITE_HIGH"
#define IO_EXP_B_PIN_00_WRITE_LOW     "IOEXP_PB_PIN00_WRITE_LOW"

// IO Expander Port B - Pin 1 operations
#define IO_EXP_B_PIN_01_SET_INPUT     "IOEXP_PB_PIN01_SET_INPUT"
#define IO_EXP_B_PIN_01_SET_OUTPUT    "IOEXP_PB_PIN01_SET_OUTPUT"
#define IO_EXP_B_PIN_01_WRITE_HIGH    "IOEXP_PB_PIN01_WRITE_HIGH"
#define IO_EXP_B_PIN_01_WRITE_LOW     "IOEXP_PB_PIN01_WRITE_LOW"

// IO Expander Port B - Pin 2 operations
#define IO_EXP_B_PIN_02_SET_INPUT     "IOEXP_PB_PIN02_SET_INPUT"
#define IO_EXP_B_PIN_02_SET_OUTPUT    "IOEXP_PB_PIN02_SET_OUTPUT"
#define IO_EXP_B_PIN_02_WRITE_HIGH    "IOEXP_PB_PIN02_WRITE_HIGH"
#define IO_EXP_B_PIN_02_WRITE_LOW     "IOEXP_PB_PIN02_WRITE_LOW"

// IO Expander Port B - Pin 3 operations
#define IO_EXP_B_PIN_03_SET_INPUT     "IOEXP_PB_PIN03_SET_INPUT"
#define IO_EXP_B_PIN_03_SET_OUTPUT    "IOEXP_PB_PIN03_SET_OUTPUT"
#define IO_EXP_B_PIN_03_WRITE_HIGH    "IOEXP_PB_PIN03_WRITE_HIGH"
#define IO_EXP_B_PIN_03_WRITE_LOW     "IOEXP_PB_PIN03_WRITE_LOW"

// IO Expander Port B - Pin 4 operations
#define IO_EXP_B_PIN_04_SET_INPUT     "IOEXP_PB_PIN04_SET_INPUT"
#define IO_EXP_B_PIN_04_SET_OUTPUT    "IOEXP_PB_PIN04_SET_OUTPUT"
#define IO_EXP_B_PIN_04_WRITE_HIGH    "IOEXP_PB_PIN04_WRITE_HIGH"
#define IO_EXP_B_PIN_04_WRITE_LOW     "IOEXP_PB_PIN04_WRITE_LOW"

// IO Expander Port B - Pin 5 operations
#define IO_EXP_B_PIN_05_SET_INPUT     "IOEXP_PB_PIN05_SET_INPUT"
#define IO_EXP_B_PIN_05_SET_OUTPUT    "IOEXP_PB_PIN05_SET_OUTPUT"
#define IO_EXP_B_PIN_05_WRITE_HIGH    "IOEXP_PB_PIN05_WRITE_HIGH"
#define IO_EXP_B_PIN_05_WRITE_LOW     "IOEXP_PB_PIN05_WRITE_LOW"

// IO Expander Port B - Pin 6 operations
#define IO_EXP_B_PIN_06_SET_INPUT     "IOEXP_PB_PIN06_SET_INPUT"
#define IO_EXP_B_PIN_06_SET_OUTPUT    "IOEXP_PB_PIN06_SET_OUTPUT"
#define IO_EXP_B_PIN_06_WRITE_HIGH    "IOEXP_PB_PIN06_WRITE_HIGH"
#define IO_EXP_B_PIN_06_WRITE_LOW     "IOEXP_PB_PIN06_WRITE_LOW"

// IO Expander Port B - Pin 7 operations
#define IO_EXP_B_PIN_07_SET_INPUT     "IOEXP_PB_PIN07_SET_INPUT"
#define IO_EXP_B_PIN_07_SET_OUTPUT    "IOEXP_PB_PIN07_SET_OUTPUT"
#define IO_EXP_B_PIN_07_WRITE_HIGH    "IOEXP_PB_PIN07_WRITE_HIGH"
#define IO_EXP_B_PIN_07_WRITE_LOW     "IOEXP_PB_PIN07_WRITE_LOW"



void ioExpanderPinInit(void);
void ioExpanderInit(void);
void ioExpanderwrite(i2c_register_t *const,uint8_t, uint8_t, uint8_t);



#endif /* IOEXPANDER_H_ */
