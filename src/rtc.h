/*
 * rtc.h
 *
 *  Created on: 2 kwi 2020
 *      Author: Daniel
 *
 *      Module: DS1307H
 */

#ifndef RTC_H_
#define RTC_H_

#include <avr/io.h>
#include "i2c_master.h"

#define DS1307_ADDR 0b11010000
#define SECOND_ADDR 0x00
#define MINUTES_ADDR 0x01
#define HOUR_ADDR 0x02

struct timeBcd{
	uint8_t hourTens;
	uint8_t hourOnes;
	uint8_t minuteTens;
	uint8_t minuteOnes;
	uint8_t secondTens;
	uint8_t secondOnes;
};

void rtcInit();
void rtcSetTime(struct timeBcd *time);
void rtcGetTime(struct timeBcd *time);
void incHourTens(uint8_t *tens, uint8_t *ones);
void incMinuteSecondTens(uint8_t *tens);
void decHourTens(uint8_t *tens, uint8_t * ones);
void decMinuteSecondTens(uint8_t *tens);
void incHourOnes(uint8_t *ones, uint8_t *tens);
void incMinuteSecondOnes(uint8_t *ones);
void decHourOnes(uint8_t *ones, uint8_t *tens);
void decMinuteSecondOnes(uint8_t *ones);
#endif /* RTC_H_ */
