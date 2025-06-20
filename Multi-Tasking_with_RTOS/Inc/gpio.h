

#ifndef GPIO_HEADER_H_
#define GPIO_HEADER_H_

#include <mcu.h>
#include <interrupt.h>

#define SET_PIN_PUSH_PULL	 0
#define SET_PIN_OPEN_DRAIN	 1

#define SET_PIN_NOPUPD		0
#define SET_PIN_PULLUP		1
#define SET_PIN_PULLDOWN	2

#define SET_PIN_INPUT			0
#define SET_PIN_OUTPUT 			1
#define SET_PIN_ALTERNATIVE		2
#define SET_PIN_ANALOG 			3

#define SET_PIN_LSPEED		0
#define SET_PIN_MSPEED		1
#define SET_PIN_HSPEED		2
#define SET_PIN_VHSPEED		3

#define AET_PIN_AF0 0
#define SET_PIN_AF1 1
#define SET_PIN_AF2 2
#define SET_PIN_AF3 3
#define SET_PIN_AF4 4
#define SET_PIN_AF5 5
#define SET_PIN_AF6 6
#define SET_PIN_AF7 7
#define SET_PIN_AF8 8
#define SET_PIN_AF9 9
#define SET_PIN_AF10 10
#define SET_PIN_AF11 11
#define SET_PIN_AF12 12
#define SET_PIN_AF13 13
#define SET_PIN_AF14 14
#define SET_PIN_AF15 15

// Structure to handle GPIO configuration and control
typedef struct {
    gpio_register_t *port;     // Pointer to the GPIO port's register base address
    uint8_t pin;               // Pin number within the port (0 to 15)
    uint8_t mode;              // Mode selection: Input, Output, Alternate Function, Analog
    uint8_t output_type;       // Output type: Push-Pull or Open-Drain
    uint8_t ouput_speed;       // Output speed: Low, Medium, Fast, High (Note: 'ouput' may be a typo, consider correcting to 'output')
    uint8_t pull_up_down;      // Pull-up/Pull-down configuration: No Pull, Pull-up, Pull-down
    uint8_t data;              // Pin state: 0 (Low) or 1 (High) - used for output or read value
    uint8_t Afmode;            // Alternate function mode: value depends on the peripheral being used
} gpio_handler_t;



uint8_t rcc_enable(uint32_t*);
uint8_t GpioSetPort(gpio_register_t*, uint8_t);
uint8_t GpioPinWrite(gpio_register_t*, uint8_t, uint8_t);
uint8_t GpioPinRead(gpio_register_t*, uint8_t);

uint8_t GpioPinSetInput(gpio_register_t*, uint8_t, uint8_t*);
uint8_t GpioPinSetPinOutput(uint32_t, uint8_t, uint8_t);

uint8_t GpioPortWrite(gpio_register_t*, uint8_t);
uint8_t GpioPortRead(gpio_register_t*, uint32_t*);
uint8_t GpioPinSet(gpio_handler_t);

uint8_t GpioIntEnable(gpio_register_t*, uint8_t, uint8_t);
uint8_t GpioIntDisable(uint8_t);

#endif /* GPIO_HEADER_H_ */
