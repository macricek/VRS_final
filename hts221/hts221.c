/*
 * hts221.c
 *
 *  Created on: Dec 6, 2020
 *      Author: marko
 */

#include "hts221.h"
#include "i2c.h"


uint8_t hts221_read_byte(uint8_t reg_addr){
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, DEVICE_ADDR_READ, 0));
}

void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, DEVICE_ADDR_WRITE, 0);
}


void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, DEVICE_ADDR_READ, 1);
}

uint16_t hts221_getTemp()
{
uint16_t T0_degC,T1_degC;
uint8_t data[4],data_single;	//temp premenne na citanie registrov

hts221_readArray(data_single, T0_degC_x8, 1);
T0_degC = (uint16_t) (data_single	/	8);
hts221_readArray(data_single, T1_degC_x8, 1);
T1_degC = (uint16_t) (data_single	/	8);

return 0;
}

uint8_t hts221_init(void)
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

	//temp device init

	lsm6ds0_write_byte(CTRL_REG1, CTRL_REG1_VAL);	//zapne senzor a da refresh rate 1Hz


	return status;
}
