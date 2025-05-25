#include <mcu.h>
#include <timer.h>
#include <gpio.h>
#include <i2c.h>
#include <uart.h>
#include <user.h>
#include <ioExpander.h>

uint8_t data = 0;
uint8_t uart_data = 0;





int main(void) {


	ENABLE_FPU();
	TimerInit(TIMER9);
	userApplicationInit();
	ioExpanderInit();
	while (1) {
		update_Data_From_Appllication();
		MilliSecondsDelay(1000);
	}
}


void delay_ms(uint32_t delay_ms) {
	while (delay_ms--);
}







