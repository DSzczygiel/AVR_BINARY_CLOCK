/*
 * main.c
 *	Binary Clock
 *	MCU ATmega328p @ 8MHz
 *
 *  Created on: 25 mar 2020
 *      Author: Daniel
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "i2c_master.h"
#include "rtc.h"
#include "encoder.h"
#include "led_display.h"
#include "brigthness_control.h"

enum mode {
	RUN=-1, H1, H2, M1, M2, S1, S2, SET
};
enum mode currentMode = RUN;
enum encoderStates currentEncoderState;
struct timeBcd currentTime;
volatile uint8_t brightnessSecondsCounter = 0;

void increaseCurrentDigit() {
	switch (currentMode) {
	case H1:
		incHourTens(&currentTime.hourTens, &currentTime.hourOnes);
		break;
	case H2:
		incHourOnes(&currentTime.hourOnes, &currentTime.hourTens);
		break;
	case M1:
		incMinuteSecondTens(&currentTime.minuteTens);
		break;
	case M2:
		incMinuteSecondOnes(&currentTime.minuteOnes);
		break;
	case S1:
		incMinuteSecondTens(&currentTime.secondTens);
		break;
	case S2:
		incMinuteSecondOnes(&currentTime.secondOnes);
		break;
	default:
		break;
	}
}

void decreaseCurrentDigit() {
	switch (currentMode) {
	case H1:
		decHourTens(&currentTime.hourTens, &currentTime.hourOnes);
		break;
	case H2:
		decHourOnes(&currentTime.hourOnes, &currentTime.hourTens);
		break;
	case M1:
		decMinuteSecondTens(&currentTime.minuteTens);
		break;
	case M2:
		decMinuteSecondOnes(&currentTime.minuteOnes);
		break;
	case S1:
		decMinuteSecondTens(&currentTime.secondTens);
		break;
	case S2:
		decMinuteSecondOnes(&currentTime.secondOnes);
		break;
	default:
		break;
	}
}

int main() {
	initEncoder();
	sei();
	rtcInit();
	initLedDisplay();
	ledDisplaySetTime(&currentTime);
	bcInit();
	while (1) {
		currentEncoderState = getEncoderState();
		if(++brightnessSecondsCounter == 5){
			adjustBrightness();
			brightnessSecondsCounter = 0;
		}
		if (currentMode == RUN) {
			_delay_ms(1000);
			rtcGetTime(&currentTime);
		} else if (currentMode == SET) {
			currentMode = RUN;
			showFullTime();
			rtcSetTime(&currentTime);
		} else {
			showOneDigit(currentMode);
			if (currentEncoderState == TURNED_RIGHT) {
				increaseCurrentDigit();
			}
			if (currentEncoderState == TURNED_LEFT) {
				decreaseCurrentDigit();
			}
			_delay_ms(100);
		}
		if (currentEncoderState == PRESSED) {
			currentMode++;
			if (currentMode > SET)
				currentMode = RUN;
		}
	}
}

