/*
 * display.c
 *
 *  Created on: Nov 23, 2020
 *      Author: Stancoj
 */

#include "display.h"

display_data_ dDisplayData = {0};
uint64_t disp_time = 0, disp_time_saved = 0;

void updateDisplay(void);
void setDigit(uint8_t pos);

/*Reset (turn-off) all the segments of display*/
void resetSegments(void)
{
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_1);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_5);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_11);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_3);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_4);
	LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_1);
}

/*Set (turn-on) all the segments of display*/
void setSegments(void)
{
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_1);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_8);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_5);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_11);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_3);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1);
}

/* Reset (turn-off) all digits*/
void resetDigits(void)
{
	LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_0);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_12);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_7);
}

/* Reset (turn-on) all digits*/
void setDigits(void)
{
	DIGIT_1_ON;
	DIGIT_2_ON;
	DIGIT_3_ON;
	DIGIT_4_ON;
	DIGIT_TIME_ON;
}

void setDecimalPoint(void)
{
	LL_GPIO_ResetOutputPin(SEGMENTDP_PORT, SEGMENTDP_PIN);
}

/* Functions to display numbers 0 - 9 */
void setOne(void)
{
	// B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
}

void setTwo(void)
{
	// A,B,G,E,D
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void setThree(void)
{
	// A,B,G,C,D
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
}

void setFour(void)
{
	// F,B,G,C
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
}

void setFive(void)
{
	// A,F,G,C,D
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
}

void setSix(void)
{
	// A,F,G,E,C,D
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
}

void setSeven(void)
{
	// A,B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
}

void setEight(void)
{
	// A,B,C,D,E,F,G
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
}

void setNine(void)
{
	// A,B,C
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}

void setZero(void)
{
	// A,B,C,D,E,F
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
}
void setA(void)
{
	// A,B,C,E,F,G,
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}
void setB(void)
{
		//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setC(void)
{
		LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setD(void)
{
		//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setE(void)
{
		LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setF(void)
{
		LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setG(void)
{
		LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setH(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setI(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setJ(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setK(void)
{
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setL(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setM(void)
{
	// A,B,D,F
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
}
void setN(void)
{
		//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
		//LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
		LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setO(void){
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	}
void setP(void){
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	}
void setR(void)
{
	// G,E
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
}
void setS(void){
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	}
void setT(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	}
void setU(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	}
void setV(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	}
void setX(void){
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
	}
void setY(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void setZ(void){
	LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}
void podjebnik(void){
	//LL_GPIO_ResetOutputPin(SEGMENTA_PORT, SEGMENTA_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTB_PORT, SEGMENTB_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTC_PORT, SEGMENTC_PIN);
	LL_GPIO_ResetOutputPin(SEGMENTD_PORT, SEGMENTD_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTE_PORT, SEGMENTE_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTF_PORT, SEGMENTF_PIN);
	//LL_GPIO_ResetOutputPin(SEGMENTG_PORT, SEGMENTG_PIN);
}








/**
 * Pre-process number before it is displayed. Extract digits of the number
 */
void displayNumber(char *c)
{

	for (int i=0;i<4;i++){
		dDisplayData.digit[i] = (uint32_t)c[i];
	}

}

/*
 * Turns required digit ON
 */
void setDigit(uint8_t pos)
{
	switch(pos)
	{
		case 0:
			DIGIT_1_ON;
			break;
		case 1:
			DIGIT_2_ON;
			break;
		case 2:
			DIGIT_3_ON;
			break;
		case 3:
			DIGIT_4_ON;
			break;
	}
}

/**
 * Display data in dDisplayData.
 * Sets every digit to display its value and decimal point.
 */
void updateDisplay(void)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		switch(dDisplayData.digit[i])
		{
			case '0':
			  setDigit(i);
			  setZero();
			  break;
			case '1':
			  setDigit(i);
			  setOne();
			  break;
			case '2':
			  setDigit(i);
			  setTwo();
			  break;
			case '3':
			  setDigit(i);
			  setThree();
			  break;
			case '4':
			  setDigit(i);
			  setFour();
			  break;
			case '5':
			  setDigit(i);
			  setFive();
			  break;
			case '6':
			  setDigit(i);
			  setSix();
			  break;
			case '7':
							setDigit(i);
							setSeven();
							break;
			case '8':
							setDigit(i);
							setEight();
							break;
			case '9':
							setDigit(i);
							setNine();
							break;

			case 'A':
							setDigit(i);
							setA();
							break;
			case 'B':
							setDigit(i);
							setB();
							break;
			case 'C':
							setDigit(i);
							setC();
							break;
			case 'D':
							setDigit(i);
							setD();
							break;
			case 'E':
							setDigit(i);
							setE();
							break;
			case 'F':
							setDigit(i);
							setF();
							break;
			case 'G':
							setDigit(i);
							setG();
							break;
			case 'H':
							setDigit(i);
							setH();
							break;
			case 'I':
							setDigit(i);
							setI();
							break;
			case 'J':
							setDigit(i);
							setJ();
							break;
			case 'K':
							setDigit(i);
							setK();
							break;
			case 'L':
							setDigit(i);
							setL();
							break;
			case 'M':
							setDigit(i);
							setM();
							break;
			case 'N':
							setDigit(i);
							setN();
							break;
			case 'O':
							setDigit(i);
							setO();
							break;
			case 'P':
							setDigit(i);
							setP();
							break;
			case 'R':
							setDigit(i);
							setR();
							break;
			case 'S':
							setDigit(i);
							setS();
							break;
			case 'T':
							setDigit(i);
							setT();
							break;
			case 'U':
							setDigit(i);
							setU();
							break;
			case 'V':
							setDigit(i);
							setV();
							break;
			case 'X':
							setDigit(i);
							setX();
							break;
			case 'Y':
							setDigit(i);
							setY();
							break;
			case 'Z':
							setDigit(i);
							setZ();
							break;

			case '_':
							setDigit(i);
							podjebnik();
							break;

			case '.':
							setDigit(i);
							setDecimalPoint();
							break;
		}


		resetDigits();
		resetSegments();
	}
}

//Update displayed data and keep display ON
void TIM3_IRQHandler(void)
{
	if(LL_TIM_IsActiveFlag_UPDATE(TIM3))
	{
		updateDisplay();
	}

	LL_TIM_ClearFlag_UPDATE(TIM3);
}

