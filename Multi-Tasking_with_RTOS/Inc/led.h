

#ifndef LED_H_
#define LED_H_
#include "main.h"

void initInbuildLed(void);
void led_effect_one(void);
void led_effect_two(void);
void led_effect_three(void);
void led_effect_four(void);
void led_off_all(void);
void startSoftwareTimer(uint8_t n);
void stopSoftwareTimer(void);
void ledPatternPrint(command_t *cmd);



#endif /* LED_H_ */
