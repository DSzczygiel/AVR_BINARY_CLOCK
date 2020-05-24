/*
 * encoder.c
 *
 *  Created on: 28 mar 2020
 *      Author: Daniel
 */

#include "encoder.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void initEncoder(){
	_currentEncoderState = NONE;

	//Set encouder pins os inputs with disabled pull-ups
	ENC_A_DDR &= ~(1 << ENC_A);
	ENC_B_DDR &= ~(1 << ENC_B);
	ENC_SW_DDR &= ~(1 << ENC_SW);

	//Interrupt settings
	EIMSK |= (1 << INT0);	//Enable INT0 interrupt
	EIMSK |= (1 << INT1);	//Enable INT1 interrupt
	EICRA |= (1 << ISC01);	//INT0 - falling edge,
	EICRA |= (1 << ISC11);	//INT1 - falling edge
}

enum encoderStates getEncoderState(){
	enum encoderStates tmp = _currentEncoderState;
	_currentEncoderState = NONE;

	return tmp;
}


ISR(INT0_vect) {
	if (!bit_is_clear(ENC_B_PIN, ENC_B)) {
		_currentEncoderState = TURNED_RIGHT;
	} else {
		_currentEncoderState = TURNED_LEFT;
	}
}

ISR(INT1_vect){
	_currentEncoderState = PRESSED;
}
