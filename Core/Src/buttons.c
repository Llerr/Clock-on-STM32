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
#include "rtc.h"

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
volatile ButtonClick haveClick = buttonNoClick;

//----------------------------------------------------------------------------------------------------------------------
void clickButton()
{
  haveClick = buttonNoClick;
  printf("clickButton %d\n",GPIO_Press_Pin);
//  static int screen = 0;/
  counterForScreens = 0;
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    --mode;
    printf("Left %d\n", mode);
    break;
  case BTN_RIGHT_Pin:
    ++mode;
    printf("Right %d\n", mode);
    break;
  case BTN_UP_Pin:
    clearMatrix();
    ++stateDev;
    break;
  case BTN_DOWN_Pin:
    clearMatrix();
    --stateDev;
    break;
  }
  if(mode < 0) mode = NUM_MAIN_SCREENS-1;
  if((NUM_MAIN_SCREENS-1) < mode) mode = 0;

  if(stateDev < 0) stateDev = stateBrightness;
  if(stateBrightness < stateDev) stateDev = 0;
  setScreenCurent();
  drawScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void longClickButton()
{
  printf("long clickButton %d\n",GPIO_Press_Pin);
  haveClick = buttonNoClick;
}

//----------------------------------------------------------------------------------------------------------------------
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//  static int number = 0;
  uint8_t state = HAL_GPIO_ReadPin(BTN_GPIO_Port, GPIO_Pin);

  GPIO_Press_Pin = GPIO_Pin;
  if(!state) //Если нажали
  {
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
    if( (CNR < CHATTER_TIME) || longPress) // Проверка на дребезг и долгое нажатие
    {
      longPress = 0;
      return;
    }
    haveClick = buttonClick; // Взведём флаги, для быстрого выхода из перрывания
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
void longClickButtonCallback()
{
  longPress = 1;
  haveClick = buttonLongClick; // Взведём флаги, для быстрого выхода из перрывания
}
