/*
 * led_display.c
 *
 *  Created on: 11 kwi 2020
 *      Author: Daniel
 */

#include "led_display.h"

uint8_t columns[6] = { COL0, COL1, COL2, COL3, COL4, COL5 };
const uint8_t _overflowValue = 4;

void initLedDisplay() {
	_curentDigit = 0;
	//Port settings, used pins as output with HIGH value
	COL_DDR |= COLUMN_MASK;
	ROW_DDR |= ROW_MASK;
	CLEAR_COLUMNS;
	CLEAR_ROWS;

	//Timer0 settings
	TCCR0B |= (1 << CS01);	//Prescaler = 8
	TIMSK0 |= (1 << TOIE0);	//Enable overflow interrupt
}

/*
 * Set structure with time to display
 */
void ledDisplaySetTime(struct timeBcd *time) {
	timeToDisplay = time;
}

/*
 * Show only one digit - used in time setting
 */
void showOneDigit(uint8_t digitPosition) {
	if (digitPosition > 5)
		return;
	TIMSK0 &= ~(1 << TOIE0);	//Disable overflow interrupt
	CLEAR_COLUMNS;
	CLEAR_ROWS;
	COL_PORT &= ~(1 << (columns[digitPosition]));
	ROW_PORT &= ~(&timeToDisplay->hourTens)[digitPosition] << 2;
}

/*
 * Show full time
 */
void showFullTime() {
	CLEAR_COLUMNS;
	CLEAR_ROWS;
	TIMSK0 |= (1 << TOIE0);	//Enable overflow interrupt
}

/*
 * Column multiplexing
 *
 * F_CPU/Prescaler/TimerTicks/_overflowValue
 * 8000000/8/256/4=~976Hz
 */
ISR(TIMER0_OVF_vect) {
	_counter++;
	if (_counter == _overflowValue) {
		CLEAR_COLUMNS;
		CLEAR_ROWS;
		COL_PORT &= ~(1 << (columns[_curentDigit]));
		ROW_PORT &= ~(&timeToDisplay->hourTens)[_curentDigit] << 2;

		_curentDigit++;
		if (_curentDigit > 5)
			_curentDigit = 0;

		_counter = 0;
	}
}
