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



int16_t hts221_getTemp()
{
	int16_t T0_degC,T1_degC,MSB_T0,MSB_T1,T0_out,T1_out,vystupna,T_out;

uint8_t data[2],data_single,pom;	//temp premenne na citanie registrov

//	tvar cisla :  MSB MSB degC(8)
pom=hts221_read_byte(T1_T0_MSB);
MSB_T0=(int16_t)(pom & 0x3)<<8;	//porovnanie s poslednymi dvoma bitmi a posun o 8
MSB_T1=(int16_t) (pom & 0xC)<<6;	//porovnanie s 3tim a 4tym od konca a posun   o 6

hts221_readArray(&data_single, T0_degC_x8, 1);
T0_degC = (int16_t) ((data_single | MSB_T0) 	/	8);

hts221_readArray(&data_single, T1_degC_x8, 1);
T1_degC = (int16_t) ((data_single| MSB_T1)	/	8);

hts221_readArray(data, T0_OUT, 2);
T0_out = (int16_t) ((int16_t)data[1] << 8 |	(int16_t)data[0]);	//spojene do velkej
hts221_readArray(data, T1_OUT, 2);
T1_out = (int16_t) ((int16_t)data[1] << 8 |	(int16_t)data[0]);	//tiez

hts221_readArray(data, T_OUT, 2);
T_out = (int16_t) ((int16_t)data[1] << 8 |	(int16_t)data[0]);	//tiez

//https://www.johndcook.com/interpolatorhelp.html
//y1 = T0_degC,y2 = T1_degC;x1 = T0Out, x2 = T1_Out, x3 = T_out
vystupna = ((T1_out - T_out)*T0_degC + (T_out - T0_out)*T1_degC) / (T1_out -T0_out);

return vystupna;
}



uint16_t hts221_getHumi()
{
	uint8_t data[2],singleData;
	uint16_t h0_RH,h1_RH,hOUT,h0_TO,h1_TO,vystupna;

	singleData=hts221_read_byte(H_0_RH);		//koef
	h0_RH=(uint16_t)singleData/2 ;

	singleData=hts221_read_byte(H_1_RH);		//koef
	h1_RH=(uint16_t)singleData/2 ;

	hts221_readArray(data, H_OUT, 2);			//hOUT
	hOUT = (int16_t) ((int16_t)data[1] << 8 |	(int16_t)data[0]);

	hts221_readArray(data, H_0_T0, 2);			//h0_T0
	h0_TO = (int16_t) ((int16_t)data[1] << 8 |	(int16_t)data[0]);

	hts221_readArray(data, H_1_T0, 2);			//h1_TO
	h1_TO = (int16_t) ((int16_t)data[1] << 8 |	(int16_t)data[0]);

	// h0_RH = y1
	// h1_RH = y2
	// hOUT  = x3
	// h0_TO = x1
	// h1_TO = x2
	vystupna = ((h1_TO - hOUT)*h0_RH + (hOUT - h0_TO)*h1_RH) / (h1_TO-h0_TO);		// % vlhkosti vzduchu

	return vystupna;
}





// data[0] 0010 0000
// data[1] 1111 1111
// velkedata = data[1]data[2] -> 1111 1111 0010 0000
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

	hts221_write_byte(CTRL_REG1, CTRL_REG1_VAL);	//zapne senzor a da refresh rate 1Hz

	uint8_t nastavenie=hts221_read_byte(CTRL_REG1);


	return status;
}


