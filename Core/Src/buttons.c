/*
 * buttons.cpp
 *
 *  Created on: Jan 28, 2021
 *      Author: lex
 */

#include <stdio.h>
#include <math.h>

#include "main.h"
#include "buttons.h"
#include "MatrixRGB.h"
#include "stm32_ub_font.h"
#include "Screens.h"
#include "tim.h"
#include "rtc.h"
#include "sensors.h"

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

uint8_t edit = 0;
int8_t editNum = 0;

void getDigits(int8_t num, int8_t *d1, int8_t *d2, int8_t *max);

//----------------------------------------------------------------------------------------------------------------------
void buttonReceiverMenu()
{
  printf("buttonReceiverMenu %d\n",GPIO_Press_Pin);
//  static int screen = 0;/
  counterForScreens = 0;
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    screenCur = screenCur->prevMode;
    printf("Left %d\n", menu);
    break;
  case BTN_RIGHT_Pin:
    screenCur = screenCur->nextMode;
    printf("Right %d\n", menu);
    break;
  case BTN_UP_Pin:
   --menu;
    if(menu < 0) menu = 0;
    printf("Up, menu %d\n", menu);
    clearMatrix();
    screenCur = screenCur->nextState;
    break;
  case BTN_DOWN_Pin:
   ++menu;
    if(menu == NUM_MENU) menu = 3;
    printf("Down, menu %d\n", menu);
    clearMatrix();
    screenCur = screenCur->prevState;
    break;
  case BTN_MID_Pin:
    printf("Work, menu %d\n", menu);
//    screenPrev = screenCur;
    screenCur->midPress(NULL);
    break;
  case BTN_SET_Pin:
    initSensors();
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void buttonReceiverTimeEdit()
{
  clearScreen();
  printf("buttonReceiverTimeEdit %d\n",GPIO_Press_Pin);
  uint8_t maxNumber = 3;
  static int8_t digit1 = 0;
  static int8_t digit2 = 0;
  static int8_t timeMax = 0;

  getDigits(editNum, &digit1, &digit2, &timeMax);

  printf("num edit: %d, digit1: %d, digit2: %d, max: %d, editNum/2: %d\n", editNum, digit1, digit2, timeMax, editNum%2);
//  static int screen = 0;/
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    --editNum;
    if(editNum < 0) editNum = maxNumber;
    getDigits(editNum, &digit1, &digit2, &timeMax);
    break;
  case BTN_RIGHT_Pin:
    ++editNum;
    if(editNum > maxNumber) editNum = 0;
    getDigits(editNum, &digit1, &digit2, &timeMax);
    break;
  case BTN_UP_Pin:
    if(editNum%2)
    {
      ++digit2;
      digit2 = (digit2 > 9)?9:digit2; // Сбросим до 9
      digit2 = ((digit1*10 + digit2) > timeMax)?timeMax%10:digit2;
    }
    else
    {
      ++digit1;
      digit1 = (digit1 > timeMax/10)?timeMax/10:digit1;
      digit2 = (digit1 == timeMax/10)?timeMax%10:digit2;
    }
    break;
  case BTN_DOWN_Pin:
    if(editNum%2)
    {
      --digit2;
      digit2 = (digit2 <0)?0:digit2;
    }
    else
    {
      --digit1;
      digit1 = (digit1 <0 )?0:digit1;
    }
    break;
  case BTN_MID_Pin:
    screenCur->midPress(NULL);
    break;
  }
  printf("num edit: %d, digit1: %d, digit2: %d, max: %d\n", editNum, digit1, digit2, timeMax);

  if(editNum<2)//Правим часы
  {
    sTimeEdit.Hours = digit1*10 + digit2;
  }
  else //Правим минуты
  {
    sTimeEdit.Minutes = digit1*10 + digit2;
  }

//  uint8_t maxNumEdit = 3;
  //  RTC_AlarmTypeDef *alarm = (RTC_AlarmTypeDef *)dataPtr; // Используем стандартную структуру. Вместо ID таймера будет маска по дням недели
  //  if(dataPtr)
  //    sTimeEdit = alarm->AlarmTime;
  //  else

  char buff[32];
  sprintf(buff, "%02d:%02d", sTimeEdit.Hours, sTimeEdit.Minutes);

  uint8_t delimSize = UB_Font_WidthPChar(':', screenCur->text[0]->font);
  uint8_t digitSize = UB_Font_WidthPChar('1', screenCur->text[0]->font); // Пока все цифры одной ширины
  textBlinkTimeEdit.x = screenCur->text[0]->x + editNum * digitSize + (editNum/2)*delimSize;
  textBlinkTimeEdit.y = screenCur->text[0]->y;
  printf("Edit num: %d, num %c, ( %d, %d)\n", editNum, buff[editNum], textBlinkTimeEdit.x, textBlinkTimeEdit.y);
  blinkText[0] = buff[editNum + editNum/2];
  blinkText[1] = '\0';

  sprintf(editText, "%02d:%02d", sTimeEdit.Hours, sTimeEdit.Minutes);
  editText[editNum + editNum/2] = 127; // Пробел под цифру
}

//----------------------------------------------------------------------------------------------------------------------
void buttonReceiverBrightEdit()
{
//  static int currBright = 255;
  int mult[] = {100, 10, 1};
  static int editNum = 0;
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    --editNum;
    if(editNum < 0) editNum = 0;
    break;
  case BTN_RIGHT_Pin:
    ++editNum;
    if(editNum > 2) editNum = 2;
    break;
  case BTN_UP_Pin:
    curBright += mult[editNum];
    if(curBright > 255) curBright -= mult[editNum];
    break;
  case BTN_DOWN_Pin:
    curBright -= mult[editNum];
    if(curBright < 0) curBright += mult[editNum];
    break;
  case BTN_MID_Pin:
    screenCur->midPress(NULL);
    break;
  }
//  brightness
  uint8_t digitSize = UB_Font_WidthPChar32('1', screenCur->text[0]->font); // Пока все цифры одной ширины
  textBlink32.x = textEdit32.x + (editNum) * digitSize;
  textBlink32.y = textEdit32.y;

//  illumination =  (3-editNum)*1000 +  textBlink32.x*100 + textBlink32.y;

  sprintf(editText, "%03d", curBright);
  editText[4]  = '\0';
  blinkText[0] = editText[editNum];
  blinkText[1] = '\0';

  editText[editNum] = 127; // Пробел под цифру

  printf("[%d, %d], %d - '%s'\n",textBlink32.x, textBlink32.y, editNum, editText);

  calcBrightPWM();
}

//----------------------------------------------------------------------------------------------------------------------
void getDigits(int8_t num, int8_t *d1, int8_t *d2, int8_t *max)
{
  if(num<2)//Правим часы
  {
    *d1 = sTimeEdit.Hours/10;
    *d2 = sTimeEdit.Hours%10;
    *max = 23;
  }
  else //Правим минуты
  {
    *d1 = sTimeEdit.Minutes/10;
    *d2 = sTimeEdit.Minutes%10;
    *max = 59;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void clickButton()
{
  haveClick = buttonNoClick;
  buttonReceiver();
  drawScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void longClickButton()
{
  printf("long clickButton %d\n",GPIO_Press_Pin);
  haveClick = buttonNoClick;
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    screenCur = screenCur->backState;
    switch(screenCur->type)
    {
    case stateTimeEdit:
      break;
    default:
      buttonReceiver = buttonReceiverMenu;
    }
    break;
  case BTN_RIGHT_Pin:
    break;
  case BTN_UP_Pin:
    break;
  case BTN_DOWN_Pin:
    break;
  case BTN_MID_Pin:
    printf("Menu \n");
    screenCur->midLongPress(NULL);
    break;
  }
  clearScreen();
  drawScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void clickMidButton()
{
  switch(screenCur->type)
  {
  case stateMenuTime:
    edit = 1;
    break;
  default:
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void initButtons()
{
  buttonReceiver = buttonReceiverMenu;
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


//----------------------------------------------------------------------------------------------------------------------
