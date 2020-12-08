/*
 * lps25hb.h
 *
 *  Created on: 8. 12. 2020
 *      Author: marko
 */
#include "main.h"

#ifndef LPS25HB_H_
#define LPS25HB_H_

#define		DEVICE_ADDR_0					0xBB
#define		DEVICE_ADDR_1					0xBA
#define		STATUS							0x27
#define 	WHO_AM_I_VALUE					0xBD
#define 	WHO_AM_I_ADDRESS				0x0F

#define 	CNTRL_REG1						0x20
#define		CNTRL_REG1_VAL					0x90 //1 001 0000

#define		PRESS_OUT_H						0X2A
#define		PRESS_OUT_L						0x29
#define		PRESS_OUT_XL					0x28


uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);
void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length);
uint8_t lps25hb_init(void);
float lps25hb_getPressure();
#endif /* LPS25HB_H_ */
