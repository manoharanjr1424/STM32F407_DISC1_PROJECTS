/*
 * Serial.h
 *
 *  Created on: Apr 24, 2026
 *      Author: Windows
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ENGINE_RPM_DEVICE_ID  0x0C0
#define TEMPERATURE_DEVICE_ID 0x0B0
#define THROTTLE_POSITION_ID  0x0D0


#define MAX_ENGINE_RPM        4000
#define MIN_ENGINE_RPM        1000
#define MAX_TEMPERATURE       150
#define MIN_TEMPERATURE       70
#define MAX_THROTTLE          60
#define MIN_THROTTLE          10

typedef enum {
	UNAUTHRIZED_ATTACK = 1,
	REPLAY_ATTACK,
	SPOOFING_ATATCK,
	FLOODING_ATTACK,
	NORMAL_MESSAGE
}attck_info;

void MainMenu (void) ;
uint8_t ReadExitStatus (void);
void UnauthorizedAttack(void);
void ReplayAttack(void);
void SpoofingAttack(void);
void FloodingAttack(void);
void NormalMessage(void);
void PrintLog(const char *str);

#endif /* SERIAL_H_ */
