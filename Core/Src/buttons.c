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

uint16_t GPIO_Press_Pin = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  static int number = 0;
  uint8_t state = HAL_GPIO_ReadPin(BTN_GPIO_Port, GPIO_Pin);
  // либо выполняем какое-то действие прямо тут, либо поднимаем флажок
//  static int x = 0;
//  static int y = 0;

  printf("\n\n%d ----------------------------------\n", number++);
  printf("Pressed button: %d, state: %d\n", GPIO_Pin, state);
  if(!state)
  {
    printf("----------\ndisable interapt\n");
    switch(GPIO_Pin)
    {
    case BTN_UP_Pin:
      HAL_NVIC_DisableIRQ(BTN_UP_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
      break;
    case BTN_DOWN_Pin:
      HAL_NVIC_DisableIRQ(BTN_DOWN_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
      break;
    case BTN_LEFT_Pin:
      HAL_NVIC_DisableIRQ(BTN_LEFT_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
      break;
    case BTN_RIGHT_Pin:
      HAL_NVIC_DisableIRQ(BTN_RIGHT_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
      break;
    case BTN_MID_Pin:
      HAL_NVIC_DisableIRQ(BTN_MID_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
      break;
    case BTN_SET_Pin:
      HAL_NVIC_DisableIRQ(BTN_SET_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
      break;
    }
    HAL_StatusTypeDef ret = HAL_TIM_Base_Start_IT(&htim3);
    if(ret!=HAL_OK) // запускаем таймер
    {
      printf("Error start timer %d\n", ret);
    }
    GPIO_Press_Pin = GPIO_Pin; // Сохраним нажатую кнопку
  }
  else
  {
    HAL_TIM_Base_Stop_IT(&htim3);
    __HAL_TIM_CLEAR_FLAG(&htim3, TIM_SR_UIF); // очищаем флаг

    printf("Button click: %d\n", GPIO_Pin);
  }
//  clearMatrix();
//  UB_Font_DrawString32(x, y, "12", &Arial_18x27, 7, 0);
//  UB_Font_DrawString(x, y, "1234567890", &Font_4x6, 7, 0);
//  UB_Font_DrawString(x, y+6, "1234567890", &Font_5x8, 7, 0);
//  UB_Font_DrawString(x, y, "1", &Arial_7x10, 7, 0);
//  UB_Font_DrawString(x+7, y, "1", &Arial_8x13, 7, 0);
//  UB_Font_DrawString(x+7+8, y, "1", &Arial_10x15, 7, 0);
//  UB_Font_DrawString(x+25, y, "12", &Arial_11x18, 7, 0);
//  UB_Font_DrawPString(x, y, "12:15", &pComic_16, 7, 0);
//  UB_Font_DrawPString(x, y, "$25.2C #36.1% D700", &pLcd_4x6, 7);
//  UB_Font_DrawPString(x, y+1, "22:15", &pDigital_7_28, 7);
//  UB_Font_DrawPString(x, y+27, "12.06.2021 BT pT @", &pLcd_4x6, 7);
  drawScreen(&mainScreen);
//  printf("[%d,%d]\n",x,y);
//  drawPointT(x, y);
//  testDraw(x, y);
//  updateScreen();
//  dumpScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void enableInterupt()
{
  printf("enableInterupt\n");
  // Сработал таймер, разрешим прерывания
  switch(GPIO_Press_Pin)
  {
  case BTN_UP_Pin:
    HAL_NVIC_EnableIRQ(BTN_UP_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
    break;
  case BTN_DOWN_Pin:
    HAL_NVIC_EnableIRQ(BTN_DOWN_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
    break;
  case BTN_LEFT_Pin:
    HAL_NVIC_EnableIRQ(BTN_LEFT_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
    break;
  case BTN_RIGHT_Pin:
    HAL_NVIC_EnableIRQ(BTN_RIGHT_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
    break;
  case BTN_MID_Pin:
    HAL_NVIC_EnableIRQ(BTN_MID_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
    break;
  case BTN_SET_Pin:
    HAL_NVIC_EnableIRQ(BTN_SET_EXTI_IRQn); // сразу же отключаем прерывания на этом пине
    break;
  }
  HAL_TIM_Base_Stop_IT(&htim3);
}

//----------------------------------------------------------------------------------------------------------------------
void longPress()
{
  printf("Long press %d\n", GPIO_Press_Pin);
  HAL_TIM_Base_Stop_IT(&htim3);
  __HAL_TIM_CLEAR_FLAG(&htim3, TIM_SR_UIF); // очищаем флаг
  enableInterupt();
}
