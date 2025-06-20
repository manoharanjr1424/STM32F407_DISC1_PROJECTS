

#include "gpio.h"

uint8_t GpioPortSet(gpio_register_t *port, uint8_t data) {

	port->MODER &= ~(0xFFFFFFFF);
	port->MODER = data;
	return SUCCESS;
}

uint8_t GpioPinSet(gpio_handler_t data) {

	if (data.port == GPIOA) {

		GPIOAEN;

	} else if (data.port == GPIOB) {

		GPIOBEN;

	} else if (data.port == GPIOC) {

		GPIOCEN;

	} else if (data.port == GPIOD) {

		GPIODEN;

	} else if (data.port == GPIOE) {

		GPIOEEN;

	} else if (data.port == GPIOF) {

		GPIOFEN;
	}


	data.port->MODER &= ~(3 << (data.pin * 2));
	data.port->MODER |= (data.mode << (data.pin * 2));

	data.port->OTYPER &= ~(1 << data.pin);
	data.port->OTYPER |= (data.output_type << data.pin);

	data.port->PUPDR &= ~(3 << (data.pin * 2));
	data.port->PUPDR |= (data.pull_up_down << (data.pin * 2));

	data.port->OSPEEDR &= ~(3 << (data.pin * 2));
	data.port->OSPEEDR |= (data.ouput_speed << (data.pin * 2));


	if(data.mode == SET_PIN_ALTERNATIVE)  {

		if (data.pin < 8) {
			data.port->AFRL &= ~(0xF << (data.pin * 4));
			data.port->AFRL |=  (data.Afmode << (data.pin * 4) );
		} else if ( data.pin < 16 ) {
			data.port->AFRH &= ~(0xF << ((data.pin - 8) * 4)  );
			data.port->AFRH |=  (data.Afmode << ((data.pin - 8)*4) );
		}
	}
	else if(data.mode == SET_PIN_ANALOG) {


	}

	return SUCCESS;

}

uint8_t GpioPinWrite(gpio_register_t *port, uint8_t pinNumber, uint8_t data) {
		port->ODR &= ~(1 << pinNumber);
		port->ODR |= (data << pinNumber);
		return SUCCESS;
}

uint8_t GpioPinRead(gpio_register_t *port, uint8_t pinNumber) {

	uint8_t inputValue = 1;

	inputValue &= ( (port->IDR) >> pinNumber);

	return inputValue;
}

uint8_t GpioPortWrite(gpio_register_t *port, uint8_t value) {
	port->ODR = value;
	return SUCCESS;
}

uint8_t GpioPortRead(gpio_register_t *port, uint32_t *valueVar) {

	*valueVar = port->IDR;
	return SUCCESS;
}

uint8_t GpioIntEnable(gpio_register_t *port,uint8_t pinNumber, uint8_t edgeType)  {


	if(port == GPIOA) {
		SYSCFG->SYSCFG_EXTICR[(pinNumber/4)] = (PAEXTIPIN << ( (pinNumber * 4) % 4));
	}
	else if (port == GPIOB) {
		SYSCFG->SYSCFG_EXTICR[(pinNumber/4)] = (PBEXTIPIN << ( (pinNumber * 4) % 4));
	}
	else if (port == GPIOC) {
		SYSCFG->SYSCFG_EXTICR[(pinNumber/4)] = (PCEXTIPIN << ( (pinNumber * 4) % 4));
	}
	else if (port == GPIOD) {
		SYSCFG->SYSCFG_EXTICR[(pinNumber/4)] = (PDEXTIPIN << ( (pinNumber * 4) % 4));
	}
	else if (port == GPIOE) {
		SYSCFG->SYSCFG_EXTICR[(pinNumber/4)] = (PEEXTIPIN << ( (pinNumber * 4) % 4));
	}
	else if (port == GPIOF) {
		SYSCFG->SYSCFG_EXTICR[(pinNumber/4)] = (PFEXTIPIN << ( (pinNumber * 4) % 4));
	}
	else if (port == GPIOG) {
		SYSCFG->SYSCFG_EXTICR[(pinNumber/4)] = (PGEXTIPIN << ( (pinNumber * 4) % 4));
	}
	else if (port == GPIOH) {
		SYSCFG->SYSCFG_EXTICR[(pinNumber/4)] = (PHEXTIPIN << ( (pinNumber * 4) % 4));
	}

	switch(edgeType) {

	case RISINGEDGE:
		EXTI->EXTI_RTSR |= (ENABLE << pinNumber);
		break;
	case FALLINGEDGE:
		EXTI->EXTI_FTSR |= (ENABLE << pinNumber);
		break;
	case BOTHEDGE:
		EXTI->EXTI_RTSR |= (ENABLE << pinNumber);
		EXTI->EXTI_FTSR |= (ENABLE << pinNumber);
		break;
	}

	EXTI->EXTI_IMR |= (ENABLE << pinNumber);

	NvicEnableInt(6);
	NvicEnableInt(7);

	return SUCCESS;
}


uint8_t GpioIntDisable(uint8_t pinNumber) {

	EXTI->EXTI_IMR &= ~(ENABLE << pinNumber);
	EXTI->EXTI_RTSR &= ~(ENABLE << pinNumber);
	EXTI->EXTI_FTSR &= ~(ENABLE << pinNumber);

	return SUCCESS;
}
