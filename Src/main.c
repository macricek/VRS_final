/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "gpio.h"
#include "lis3mdltr.h"
#include "lsm6ds0.h"
#include <hts221.h>
#include <lps25hb.h>
#include <math.h>
#include "tim.h"
#include "display.h"


uint8_t temp = 0;
float mag[3], acc[3], tlak=0;
float azi,r,nadmorska;

float teplota = 0;
uint8_t vlhkost = 0;



void SystemClock_Config(void);




int main(void)
{
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();

  setSegments();
  setDigits();

  LL_mDelay(2000);

  resetDigits();
  resetSegments();

  MX_TIM3_Init();

  lsm6ds0_init();
  hts221_init();
  lps25hb_init();
  lis3mdl_init();

  while (1)
  {
	  teplota = hts221_getTemp();
	  vlhkost = hts221_getHumi();
	  tlak = lps25hb_getPressure();
	  // void lis3mdl_get_mag(float* x, float* y, float* z)
	  lis3mdl_get_mag(&mag[0],&mag[1],&mag[2]);
	  azi=lis3mdl_get_azimut(mag[0],mag[1]);
	  nadmorska = nadmorska_vyska(tlak,teplota);
	  LL_mDelay(50);
  }
}
float nadmorska_vyska(float tlak,float teplota)
{
	//https://keisan.casio.com/exec/system/1224585971
	float z2;
	const float pom = 1/5.257;
	const float TK = 273.15;
	const float p0 = 101325 / 100.0f;
	float akt_t = teplota + TK;
	float mocnina = pow(p0/tlak,pom);

	z2 = ((mocnina-1)*(TK + 15)) / 0.0065;

	return z2;
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  if(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0)
  {
  Error_Handler();  
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {
    
  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  
  }
  LL_Init1msTick(8000000);
  LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);
  LL_SetSystemCoreClock(8000000);
  LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
