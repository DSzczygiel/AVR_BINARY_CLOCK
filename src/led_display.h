/*
 * led_display.h
 *
 *  Created on: 11 kwi 2020
 *      Author: Daniel
 *
 *     	Multiplexed LED matrix
 *     	Turned on with LOW state
 */

#ifndef LED_DISPLAY_H_
#define LED_DISPLAY_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "rtc.h"

#define ROW_DDR DDRB
#define COL_DDR DDRD
#define ROW_PORT PORTB
#define COL_PORT PORTD

#define COL0 PD0
#define COL1 PD1
#define COL2 PD4
#define COL3 PD5
#define COL4 PD6
#define COL5 PD7

#define COLUMN_MASK 0b11110011
#define ROW_MASK 0b00111100
#define CLEAR_COLUMNS COL_PORT |= COLUMN_MASK;
#define CLEAR_ROWS ROW_PORT |= ROW_MASK

volatile uint8_t _curentDigit;
volatile uint8_t _counter;
struct timeBcd *timeToDisplay;

void initLedDisplay();
void ledDisplaySetTime(struct timeBcd *time);
void showOneDigit(uint8_t digitPosition);
void showFullTime();

#endif /* LED_DISPLAY_H_ */
