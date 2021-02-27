/*
 * buttons.cpp
 *
 *  Created on: Jan 28, 2021
 *      Author: lex
 */

#include <stdio.h>

#include "main.h"
#include "buttons.h"
#include "MatrixRGB.h"
#include "stm32_ub_font.h"
#include "Screens.h"
#include "tim.h"

//#define BTN_RESET_EXTI_IRQn EXTI0_IRQn
//#define BTN_SET_EXTI_IRQn EXTI1_IRQn
//#define BTN_MID_EXTI_IRQn EXTI2_IRQn
//#define BTN_RIGHT_EXTI_IRQn EXTI3_IRQn
//#define BTN_LEFT_EXTI_IRQn EXTI4_IRQn
//#define BTN_DOWN_EXTI_IRQn EXTI9_5_IRQn
//#define BTN_UP_EXTI_IRQn EXTI9_5_IRQn

#define CHATTER_TIME 700 ///< Время для подавления дребезга в миллисекундах

volatile uint16_t GPIO_Press_Pin = 0;
volatile uint8_t longPress = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//  static int number = 0;
  uint8_t state = HAL_GPIO_ReadPin(BTN_GPIO_Port, GPIO_Pin);

  GPIO_Press_Pin = GPIO_Pin;
  if(!state) //Если нажали
  {
//    printf("Pressed button: %d, curTime: %lu \n", GPIO_Pin, curTime);
    longPress = 0;

    __HAL_TIM_CLEAR_FLAG(&htim3, TIM_SR_UIF); // очищаем флаг
    HAL_TIM_Base_Start_IT(&htim3);
    return;
  }
  else //Если отпустили
  {
    uint32_t CNR = htim3.Instance->CNT;
    HAL_TIM_Base_Stop_IT(&htim3);
    htim3.Instance->CNT = 0;
//    printf("Release button: %d, CNR: %lu\n", GPIO_Pin, CNR);
    if( (CNR < CHATTER_TIME) || longPress) // Проверка на дребезг и долгое нажатие
    {
      longPress = 0;
      return;
    }

    clickButton();
  }
}

//----------------------------------------------------------------------------------------------------------------------
void enableInterupt()
{
  HAL_NVIC_EnableIRQ(BTN_UP_EXTI_IRQn);
  HAL_NVIC_EnableIRQ(BTN_DOWN_EXTI_IRQn);
  HAL_NVIC_EnableIRQ(BTN_LEFT_EXTI_IRQn);
  HAL_NVIC_EnableIRQ(BTN_RIGHT_EXTI_IRQn);
  HAL_NVIC_EnableIRQ(BTN_MID_EXTI_IRQn);
  HAL_NVIC_EnableIRQ(BTN_SET_EXTI_IRQn);
}

//----------------------------------------------------------------------------------------------------------------------
void disableInterupt()
{
    HAL_NVIC_DisableIRQ(BTN_UP_EXTI_IRQn);
    HAL_NVIC_DisableIRQ(BTN_DOWN_EXTI_IRQn);
    HAL_NVIC_DisableIRQ(BTN_LEFT_EXTI_IRQn);
    HAL_NVIC_DisableIRQ(BTN_RIGHT_EXTI_IRQn);
    HAL_NVIC_DisableIRQ(BTN_MID_EXTI_IRQn);
    HAL_NVIC_DisableIRQ(BTN_SET_EXTI_IRQn);
}

//----------------------------------------------------------------------------------------------------------------------
void clearFlag()
{
  __HAL_GPIO_EXTI_CLEAR_FLAG(BTN_UP_EXTI_IRQn);
  __HAL_GPIO_EXTI_CLEAR_FLAG(BTN_DOWN_EXTI_IRQn);
  __HAL_GPIO_EXTI_CLEAR_FLAG(BTN_LEFT_EXTI_IRQn);
  __HAL_GPIO_EXTI_CLEAR_FLAG(BTN_RIGHT_EXTI_IRQn);
  __HAL_GPIO_EXTI_CLEAR_FLAG(BTN_MID_EXTI_IRQn);
  __HAL_GPIO_EXTI_CLEAR_FLAG(BTN_SET_EXTI_IRQn);
}

//----------------------------------------------------------------------------------------------------------------------
void clickButton()
{
  printf("Click %d\n", GPIO_Press_Pin);
}

//----------------------------------------------------------------------------------------------------------------------
void longClickButton()
{
  printf("Long click %d\n", GPIO_Press_Pin);
  longPress = 1;
}
