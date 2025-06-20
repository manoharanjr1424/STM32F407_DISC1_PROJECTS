

#ifndef RTC_H_
#define RTC_H_

#include "main.h"
#include "task.h"
#define RTC_SLAVE_ADDRESS 0x68
#define RTC_SLAVE_WRITEADDR 0xD0
#define RTC_SLAVE_READADDR 0xD1

// Timekeeping Registers
#define RTC_SEC_REG          0x00  // Seconds
#define RTC_MIN_REG          0x01  // Minutes
#define RTC_HOUR_REG         0x02  // Hours
#define RTC_DAY_REG          0x03  // Day (1–7)
#define RTC_DATE_REG         0x04  // Date (1–31)
#define RTC_MONTH_REG        0x05  // Month / Century
#define RTC_YEAR_REG         0x06  // Year (00–99)

// Alarm 1 Registers
#define RTC_ALM1_SEC_REG     0x07  // Alarm 1 Seconds
#define RTC_ALM1_MIN_REG     0x08  // Alarm 1 Minutes
#define RTC_ALM1_HOUR_REG    0x09  // Alarm 1 Hours
#define RTC_ALM1_DATE_REG    0x0A  // Alarm 1 Date / Day

// Alarm 2 Registers
#define RTC_ALM2_MIN_REG     0x0B  // Alarm 2 Minutes
#define RTC_ALM2_HOUR_REG    0x0C  // Alarm 2 Hours
#define RTC_ALM2_DATE_REG    0x0D  // Alarm 2 Date / Day

// Control & Status Registers
#define RTC_CONTROL_REG      0x0E  // Control Register
#define RTC_STATUS_REG       0x0F  // Status Register

// Aging and Temperature
#define RTC_AGING_OFFSET_REG 0x10  // Aging Offset
#define RTC_TEMP_MSB_REG     0x11  // Temp MSB
#define RTC_TEMP_LSB_REG     0x12  // Temp LSB



typedef struct {
	uint8_t date;
	uint8_t mon;
	uint8_t year;
	uint8_t hrs;
	uint8_t min;
	uint8_t sec;
}timeDate_t;


int  bcd2Decimal (uint8_t);
int  decimal2Bcd (int);
int8_t writeDatatoRTC (timeDate_t *);
int8_t getDataFromRTC (timeDate_t *);
void getTimeData(char *printBuffer);
void getDateData(char *printBuffer);
int8_t setTime (uint8_t, uint8_t, uint8_t);
int8_t setDate (uint8_t date, uint8_t mon, uint8_t year);
int8_t RTCInit(void);
void RTCMenu(void);
void timeCommandExtracter(command_t *cmd);
void dateCommandExtracter(command_t *cmd);

extern timeDate_t timedata;

#endif /* RTC_H_ */
