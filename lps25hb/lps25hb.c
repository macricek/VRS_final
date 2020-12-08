/*
 * lps25hb.c
 *
 *  Created on: 8. 12. 2020
 *      Author: marko
 */

#include "i2c.h"
#include "lps25hb.h"

uint8_t lps25hb_read_byte(uint8_t reg_addr){
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, DEVICE_ADDR_0, 0));
}

void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, DEVICE_ADDR_0, 0);
}


void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, DEVICE_ADDR_0, 1);
}


float lps25hb_getPressure()
{
uint8_t pressH,pressL,pressXL;
pressH = lps25hb_read_byte(PRESS_OUT_H);
pressL = lps25hb_read_byte(PRESS_OUT_L);
pressXL = lps25hb_read_byte(PRESS_OUT_XL);

int complement = pressH & pressL & pressXL;
return complement / 4096.0f;
}


uint8_t lps25hb_init(void)
{

	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(WHO_AM_I_ADDRESS);

	if(val == WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		val = hts221_read_byte(WHO_AM_I_ADDRESS);
		if(val == WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
		}
	}

	//lps device init
	lps25hb_write_byte(CNTRL_REG1, CNTRL_REG1_VAL);	//zapne a cita kazdu sekundu
	return status;
}
