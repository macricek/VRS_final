/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "stm32f3xx_ll_exti.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Pinout Configuration
*/
void MX_GPIO_Init(void)
{

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

  /**/
  LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_8|LL_GPIO_PIN_11|LL_GPIO_PIN_12);					 // A

  /**/
  LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_1|LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_0);																 // B

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_3|LL_GPIO_PIN_4|LL_GPIO_PIN_12|LL_GPIO_PIN_8|LL_GPIO_PIN_11|LL_GPIO_PIN_2|LL_GPIO_PIN_7; // A
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_1|LL_GPIO_PIN_4|LL_GPIO_PIN_5|LL_GPIO_PIN_0;																		 // B
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE3);

   /*Skopirovane z vygenerovaneho kodu pomocneho projektu pre tlacitko*/
   LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_3, LL_GPIO_PULL_NO);

   /**/
   LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_3, LL_GPIO_MODE_INPUT);

   LL_EXTI_InitTypeDef EXTI_InitStruct = {0};
   /**/
   EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_3;
   EXTI_InitStruct.Line_32_63 = LL_EXTI_LINE_NONE;
   EXTI_InitStruct.LineCommand = ENABLE;
   EXTI_InitStruct.Mode = LL_EXTI_MODE_IT;
   EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_RISING;
   LL_EXTI_Init(&EXTI_InitStruct);

   /* EXTI interrupt init*/
   NVIC_SetPriority(EXTI3_IRQn,NVIC_PRIORITYGROUP_2);
   NVIC_EnableIRQ(EXTI3_IRQn);

   RCC->AHBENR |= RCC_AHBENR_GPIOAEN;		//enabled clock
   GPIOB->MODER &= ~(GPIO_MODER_MODER3);		//moder reset -> INPUT
   GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR3);		//transistors
   GPIOB->PUPDR |= GPIO_PUPDR_PUPDR3_0;

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
