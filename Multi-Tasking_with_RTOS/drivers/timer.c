


#include "mcu.h"
#include "timer.h"
#include "interrupt.h"


uint32_t g_timeOutFlag = 0;


void TIM1_BRK_TIM9_IRQHandler (void) {

	if( TIMER9->TIM_SR & 1)
	{
		TIMER9->TIM_SR &= ~(1 << 0);
		g_timeOutFlag = 1;
	}

}

void TimerInit(tmr_9_register_t *Timer) {

	RCC->APB2ENR |= (1 << 16);
//	Timer->TIM_PSC = 83;
//	Timer->TIM_CNT = 0;
//	Timer->TIM_ARR = 0;

	NvicEnableInt(24);
}


void TimerEnable(tmr_9_register_t *Timer, uint32_t PreLoad) {

	Timer->TIM_PSC = 15;
	Timer->TIM_CNT = 0;
	Timer->TIM_ARR = PreLoad;
	Timer->TIM_DIER |= (1 << 0);
	Timer->TIM_CR1 |= (1 << 7) | (1 << 0);

}


void TimerPrescaleSet(uint32_t ui32Base, uint32_t ui32preScaleValue) {


}


void TimerDisable(tmr_9_register_t *Timer) {

	Timer->TIM_CR1 &= ~(1 << 0);
}

void TimerLoadValue(uint32_t ui32Base) {


}
void MilliSecondsDelay(uint32_t delay) {

	while(delay) {
	MicroSecondsDelay(1000);
	delay--;
	}
}

void MicroSecondsDelay(uint32_t delay) {

	uint32_t ui32LocalLoadValue = 0;
	uint32_t ui32LocalRemining = delay;
	while(ui32LocalRemining > 0 )
	{

		if( ui32LocalRemining > 65536) {
			ui32LocalLoadValue = 65536;
			ui32LocalRemining -= 65536;
		} else {
			ui32LocalLoadValue = ui32LocalRemining;
			ui32LocalRemining = 0;
		}

		g_timeOutFlag = 0;
		TimerEnable(TIMER9,ui32LocalLoadValue);
		while(!g_timeOutFlag);
		TimerDisable(TIMER9);
	}

}
void SecondsDelay(uint32_t delay) {

	while(delay--)
	{
		MilliSecondsDelay(1000);
	}
}

