/*
 * encoder.h
 *
 *  Created on: 28 mar 2020
 *      Author: Daniel
 *
 *      EC11 rotary encoder used for time setting
 *      Hardware debounced
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#define ENC_A_DDR DDRD
#define ENC_B_DDR DDRB
#define ENC_SW_DDR DDRD

#define ENC_A_PIN PIND
#define ENC_B_PIN PINB
#define ENC_SW_PIN PIND

#define ENC_A PD2
#define ENC_B PB0
#define ENC_SW PD3

enum encoderStates {NONE, TURNED_LEFT, TURNED_RIGHT, PRESSED};
volatile enum encoderStates _currentEncoderState;

void initEncoder();

enum encoderStates getEncoderState();
#endif /* ENCODER_H_ */
