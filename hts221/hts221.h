/*
 * hts221.h
 *
 *  Created on: Dec 6, 2020
 *      Author: marko
 */
#include "main.h"
#ifndef HTS221_H_
#define HTS221_H_

#define		DEVICE_ADDRESS					0x5F
#define		DEVICE_ADDR_WRITE				0xBE
#define		DEVICE_ADDR_READ				0xBF

#define 	WHO_AM_I_VALUE					0xBC
#define 	WHO_AM_I_ADDRESS				0x0F
#define 	CTRL_REG1 						0x20
#define 	CTRL_REG1_VAL					0x81	//1 0000 0 01 -> 1Hz + boot



#define		T0_degC_x8						0x32
#define		T1_degC_x8						0x33

#define		T1_T0_MSB						0x35
#define		T0_OUT							0x3C
#define		T1_OUT							0x3E
#define		T_OUT							0x2A

uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);
void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length);
uint8_t hts221_init(void);
int16_t hts221_getTemp();

#endif /* HTS221_H_ */
