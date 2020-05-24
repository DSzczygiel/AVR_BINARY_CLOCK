/*
 * rtc.c
 *
 *  Created on: 2 kwi 2020
 *      Author: Daniel
 */

#include "rtc.h"
#include "i2c_master.h"

/*
 * Start clock by setting CH bit and set SCK clock to 100kHz
 */
void rtcInit() {
	TWBR = 32;
	i2c_init();
	i2c_start(DS1307_ADDR + I2C_WRITE);
	i2c_write(SECOND_ADDR);
	i2c_start(DS1307_ADDR + I2C_READ);

	uint8_t tmp = i2c_read_nack();
	i2c_start(DS1307_ADDR + I2C_WRITE);
	i2c_write(SECOND_ADDR);
	i2c_write(tmp & 0b01111111);
}

/*
 * Set time from given struct to  DS1307
 */
void rtcSetTime(struct timeBcd *time) {
	i2c_start(DS1307_ADDR + I2C_WRITE);
	i2c_write(SECOND_ADDR);
	uint8_t tmp = 0;
	tmp = ((time->secondTens & 0b00000111) << 4)
			+ (time->secondOnes & 0b00001111);
	i2c_write(tmp);
	tmp = (time->minuteTens << 4) + (time->minuteOnes & 0b00001111);
	i2c_write(tmp);
	tmp = ((time->hourTens & 0b00000011) << 4) + (time->hourOnes & 0b00001111);
	i2c_write(tmp);
	i2c_stop();
}

/*
 *Read time from DS1307 and save in given struct
 */
void rtcGetTime(struct timeBcd *time) {
	i2c_start(DS1307_ADDR + I2C_WRITE);
	i2c_write(SECOND_ADDR);
	i2c_start(DS1307_ADDR + I2C_READ);

	uint8_t tmp = i2c_read_ack();
	time->secondOnes = (tmp & 0b00001111);
	time->secondTens = (tmp >> 4);

	tmp = i2c_read_ack();
	time->minuteOnes = (tmp & 0b00001111);
	time->minuteTens = (tmp >> 4);

	tmp = i2c_read_nack();
	time->hourOnes = (tmp & 0b00001111);
	time->hourTens = (tmp >> 4);
	i2c_stop();

}

/*
 *Inc/decrease digits in BCD and check correct ranges
 */
void incHourTens(uint8_t *tens, uint8_t *ones) {
	if((*tens) == 1){
		(*ones) = 0;
		(*tens)++;
		return;
	}else if ((*tens) == 2) {
		*tens = 0;
		return;
	}else{
		(*tens)++;
	}
}

void incMinuteSecondTens(uint8_t *tens) {
	if ((*tens) == 5) {
		*tens = 0;
		return;
	}
	(*tens)++;
}

void decHourTens(uint8_t *tens, uint8_t * ones) {
	if ((*tens) == 0) {
		*tens = 2;
		if((*ones) > 3){
			*ones = 0;
		}
		return;
	}
	(*tens)--;
}
void decMinuteSecondTens(uint8_t *tens) {
	if ((*tens) == 0) {
		*tens = 5;
		return;
	}
	(*tens)--;
}

void incHourOnes(uint8_t *ones, uint8_t *tens) {
	if((*tens) == 2){
		if ((*ones) == 3) {
			*ones = 0;
			return;
		}
		(*ones)++;
	}else{
		if ((*ones) == 9) {
			*ones = 0;
			return;
		}
		(*ones)++;
	}

}

void incMinuteSecondOnes(uint8_t *ones) {
	if ((*ones) == 9) {
		*ones = 0;
		return;
	}
	(*ones)++;
}

void decHourOnes(uint8_t *ones, uint8_t *tens) {
	if((*tens) == 2){
		if ((*ones) == 0) {
			*ones = 3;
			return;
		}
	}else{
		if ((*ones) == 0) {
			*ones = 9;
			return;
		}
	}
	(*ones)--;
}

void decMinuteSecondOnes(uint8_t *ones) {
	if ((*ones) == 0) {
		*ones = 9;
		return;
	}
	(*ones)--;
}
