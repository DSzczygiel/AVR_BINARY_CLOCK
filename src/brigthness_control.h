/*
 * brigthness_control.h
 *
 *  Created on: 15 kwi 2020
 *      Author: Daniel
 *
 *		Using LDR to get ambient light level
 *		and setting PWM duty cycle accordingly
 */

#ifndef BRIGTHNESS_CONTROL_H_
#define BRIGTHNESS_CONTROL_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define LDR_DDR DDRC
#define PWM_DDR DDRB
#define LDR_PORT PORTC
#define PWM_PORT PORTB
#define LDR PC0
#define PWM PB1

void bcInit();
void adjustBrightness();
void _startConversion();

#endif /* BRIGTHNESS_CONTROL_H_ */
