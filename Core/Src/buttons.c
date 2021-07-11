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
#include "utils.h"
#include "audio.h"

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

//Максимальные значения для часов
uint8_t maxHours = 23;   ///< Часов в сутках
uint8_t maxMinutes = 59; ///< Минут в часе
uint8_t maxSeconds = 59; ///< Секунд в минуте

//Максимальные значения для даты
uint8_t maxDays = 31;  ///< Дней в месяце (в коде корректируется)
uint8_t maxMouns = 12; ///< Количество месяцев в году
uint maxYear = 99;     ///< Максимальное значение года

uint8_t edit = 0;


//----------------------------------------------------------------------------------------------------------------------
void buttonReceiverMenu()
{
  printf("buttonReceiverMenu %d\n",GPIO_Press_Pin);
//  static int screen = 0;/
  // Сбросим счётчики
  counterForScreens = 0;
  resetCounter = 0;

//  play(&buttonSound, 0);
  clearScreen();
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    play(&clockSound, 0);
    screenCur = screenCur->prevMode;
//    printf("Left %d\n", menu);
    break;
  case BTN_RIGHT_Pin:
    play(&buttonSound, 0);
    screenCur = screenCur->nextMode;
//    printf("Right %d\n", menu);
    break;
  case BTN_UP_Pin:
//   --menu;
//    if(menu < 0) menu = 0;
//    printf("Up, menu %d\n", menu);
    clearMatrix();
    screenCur = screenCur->nextState;
    break;
  case BTN_DOWN_Pin:
//   ++menu;
//    if(menu == NUM_MENU) menu = 3;
//    printf("Down, menu %d\n", menu);
    clearMatrix();
    screenCur = screenCur->prevState;
    break;
  case BTN_MID_Pin:
//    printf("Work, menu %d\n", menu);
//    screenPrev = screenCur;
    screenCur->midPress(screenCur);
    break;
  case BTN_SET_Pin:
    clearMatrix();
    screenCur = screenCur->setState;
//    initSensors();
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void buttonReceiverTimeEdit()
{
  int mult[] = {10, 1};
  uint8_t maxNumber = 3;
  static int8_t editNum = 0;
  int8_t delta = 0;
//  static int8_t timeMax = 0;

  clearScreen();
//  editVal = (editNum<2)?sTimeEdit.Hours:sTimeEdit.Minutes;
  printf("buttonReceiverTimeEdit %d\n",GPIO_Press_Pin);

  // Если номер редактируемой цифры меньше 2, то правим часы, иначе минуты
  //  static int screen = 0;/
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    --editNum;
    if(editNum < 0) editNum = maxNumber;
    break;
  case BTN_RIGHT_Pin:
    ++editNum;
    if(editNum > maxNumber) editNum = 0;
    break;
  case BTN_UP_Pin:
    delta = mult[editNum%2];
    break;
  case BTN_DOWN_Pin:
    delta = -mult[editNum%2];
    break;
  case BTN_MID_Pin:
    screenCur->midPress(NULL);
    break;
  }
  printf("Time: %02d:%02d, num:%d - edit val: %d\n", sTimeEdit.Hours, sTimeEdit.Minutes, editNum, delta);

  if(editNum<2)//Правим часы
  {
    sTimeEdit.Hours += delta;
    sTimeEdit.Hours -= (sTimeEdit.Hours > maxHours)?delta:0;
  }
  else //Правим минуты
  {
    sTimeEdit.Minutes += delta;
    sTimeEdit.Minutes -= (sTimeEdit.Minutes > maxMinutes)?delta:0;
  }

  sprintf(editText, "%02d:%02d", sTimeEdit.Hours, sTimeEdit.Minutes);

  uint8_t delimSize = UB_Font_WidthPChar16(':', screenCur->text[0]->font);
  uint8_t digitSize = UB_Font_WidthPChar16('1', screenCur->text[0]->font); // Пока все цифры одной ширины

  textBlinkTimeEdit.x = screenCur->text[0]->x + editNum * digitSize + (editNum/2)*delimSize;
  textBlinkTimeEdit.y = screenCur->text[0]->y;

  printf("Edit num: %d, val %c, ( %d, %d)\n", editNum, editText[editNum], textBlinkTimeEdit.x, textBlinkTimeEdit.y);
  blinkText[0] = editText[editNum + editNum/2];
  blinkText[1] = '\0';
  printf("Blink text: (%s)\n", blinkText);

  editText[editNum + editNum/2] = 127; // Пробел под цифру
}

//----------------------------------------------------------------------------------------------------------------------
void buttonReceiverAlarmEdit()
{
  int mult[] = {10, 1};
  uint8_t maxNumber = 3 + 8;
  static int8_t editNum = 0;
  int8_t delta = 0;

//  static int8_t timeMax = 0;

  clearScreen();
//  editVal = (editNum<2)?sTimeEdit.Hours:sTimeEdit.Minutes;
  printf("buttonReceiverAlarmEdit %d\n",GPIO_Press_Pin);

  // Если номер редактируемой цифры меньше 2, то правим часы, иначе минуты
  //  static int screen = 0;/
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    --editNum;
    if(editNum < 0) editNum = maxNumber;
    break;
  case BTN_RIGHT_Pin:
    ++editNum;
    if(editNum > maxNumber) editNum = 0;
    break;
  case BTN_UP_Pin:
    delta = mult[editNum%2];
    break;
  case BTN_DOWN_Pin:
    delta = -mult[editNum%2];
    break;
  case BTN_MID_Pin:
    screenCur->midPress(NULL);
    return;
    break;
  }
  printf("Time: %02d:%02d, num:%d - edit val: %d\n", alarmEdit.alarmTime.Hours, alarmEdit.alarmTime.Minutes, editNum, delta);

  sprintf(editText, "%02d:%02d", alarmEdit.alarmTime.Hours, alarmEdit.alarmTime.Minutes);
  sprintf(editTextDays, "MTWTF");
  sprintf(editTextOffDays, "SS");
  sprintf(editTextAlarmOn, "1");

  if(editNum < 4) // Правим время
  {
    screenCur->blink = &textBlinkTimeEdit;
    if(editNum<2)//Правим часы
    {
      alarmEdit.alarmTime.Hours += delta;
      alarmEdit.alarmTime.Hours -= (alarmEdit.alarmTime.Hours > maxHours)?delta:0;
    }
    else  //Правим минуты
    {
      alarmEdit.alarmTime.Minutes += delta;
      alarmEdit.alarmTime.Minutes -= (alarmEdit.alarmTime.Minutes > maxMinutes)?delta:0;
    }
    // Продублируем, для отображения изменений.
    sprintf(editText, "%02d:%02d", alarmEdit.alarmTime.Hours, alarmEdit.alarmTime.Minutes);

    uint8_t delimSize = UB_Font_WidthPChar16(':', screenCur->text[0]->font);
    uint8_t digitSize = UB_Font_WidthPChar16('1', screenCur->text[0]->font); // Пока все цифры одной ширины

    textBlinkTimeEdit.x = screenCur->text[0]->x + editNum * digitSize + (editNum/2)*delimSize;
    textBlinkTimeEdit.y = screenCur->text[0]->y;

    printf("Edit num: %d, val %c, ( %d, %d)\n", editNum, editText[editNum], textBlinkTimeEdit.x, textBlinkTimeEdit.y);
    blinkText[0] = editText[editNum + editNum/2];
    blinkText[1] = '\0';

    editText[editNum + editNum/2] = 127; // Пробел под цифру
  }
  else if(editNum < 4 + 5) // Правим будни
  {
    if(delta > 0)
      alarmSetDay(&alarmEdit, editNum - 3);
    else if(delta < 0)
      alarmResetDay(&alarmEdit, editNum - 3);

    screenCur->blink = &textBlinkDays;
    textBlinkDays.x = screenCur->text[1]->x + (editNum-4) * 7;
    textBlinkDays.y = screenCur->text[1]->y;

    blinkText[0] = editTextDays[editNum - 4];
    blinkText[1] = '\0';

    editTextDays[editNum - 4] = ' '; //Шрифт моноширинный
    printf("Work day\n");
  }
  else if(editNum < 4 + 5 + 2) // Правим выходные
  {
    if(delta > 0)
      alarmSetDay(&alarmEdit, (editNum - 3)%7);
    else if(delta < 0)
      alarmResetDay(&alarmEdit, (editNum - 3)%7);

    screenCur->blink = &textBlinkOffDays;
    textBlinkOffDays.x = screenCur->text[2]->x + (editNum-4-5) * 7;
    textBlinkOffDays.y = screenCur->text[2]->y;

    blinkText[0] = 'S';
    blinkText[1] = '\0';

    editTextOffDays[editNum - 4 - 5] = ' '; //Шрифт моноширинный
    printf("Off day\n");
  }
  else  // Правим однократный будильник
  {
    if(delta > 0)
      alarmSetState(&alarmEdit, 1);
    else if(delta < 0)
      alarmSetState(&alarmEdit, 0);

    screenCur->blink = &textBlinkAlarmOn;
    textBlinkAlarmOn.x = screenCur->text[3]->x;
    textBlinkAlarmOn.y = screenCur->text[3]->y;

    blinkText[0] = 'O';
    blinkText[1] = 'n';
    blinkText[2] = '\0';

    editTextAlarmOn[0] = ' ';
    printf("1 day\n");
  }
  drawBars(&alarmEdit);
  printf("Edit num: %d, Blink text: (%s)\n", editNum, blinkText);
}

//----------------------------------------------------------------------------------------------------------------------
void buttonReceiverDateEdit()
{
  int mult[] = {10, 1};
  uint8_t maxNumber = 5;
  static int8_t editNum = 0;
  int8_t delta = 0;
//  static int8_t timeMax = 0;

  clearScreen();
//  editVal = (editNum<2)?sTimeEdit.Hours:sTimeEdit.Minutes;
  printf("--- buttonReceiverDateEdit %d ---\n",GPIO_Press_Pin);

  // Если номер редактируемой цифры меньше 2, то правим часы, иначе минуты
  //  static int screen = 0;/
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    --editNum;
    if(editNum < 0) editNum = maxNumber;
    break;
  case BTN_RIGHT_Pin:
    ++editNum;
    if(editNum > maxNumber) editNum = 0;
    break;
  case BTN_UP_Pin:
    delta = mult[editNum%2];
    break;
  case BTN_DOWN_Pin:
    delta = -mult[editNum%2];
    break;
  case BTN_MID_Pin:
    screenCur->midPress(NULL);
    break;
  }
//  printf("Time: %02d:%02d, num:%d - edit val: %d\n", sTimeEdit.Hours, sTimeEdit.Minutes, editNum, delta);

  if(editNum<2) //Правим дни
  {
    sDateEdit.Date += delta;
    sDateEdit.Date -= (sDateEdit.Date > maxDays)?delta:0;
  }
  else if(editNum<4) //Правим месяц
  {
    sDateEdit.Month += delta;
    sDateEdit.Month -= (sDateEdit.Month > maxMouns)?delta:0;
  }
  else // Правим год
  {
    sDateEdit.Year += delta;
    sDateEdit.Year -= (sDateEdit.Year > maxYear)?delta:0;
 }

  sprintf(editText, "%02d.%02d.%02d", sDateEdit.Date, sDateEdit.Month, sDateEdit.Year);

  uint8_t delimSize = UB_Font_WidthPChar32('.', screenCur->text[0]->font);
  uint8_t digitSize = UB_Font_WidthPChar32('1', screenCur->text[0]->font); // Пока все цифры одной ширины

  textBlink32.x = screenCur->text[0]->x + editNum * digitSize + (editNum/2)*delimSize;
  textBlink32.y = screenCur->text[0]->y;

  printf("Edit num: %d, val %c, ( %d, %d)\n", editNum, editText[editNum], textBlink32.x, textBlink32.y);
  blinkText[0] = editText[editNum + editNum/2];
  blinkText[1] = '\0';
  printf("Blink text: (%s)\n", blinkText);
  editText[editNum + editNum/2] = 127; // Пробел под цифру
  clearScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void buttonReceiverCountdownEdit()
{
  int mult[] = {10, 1};
  uint8_t maxNumber = 5;
  static int8_t editNum = 0;
  int8_t delta = 0;
//  static int8_t timeMax = 0;

  clearScreen();
//  editVal = (editNum<2)?sTimeEdit.Hours:sTimeEdit.Minutes;
  printf("--- buttonReceiverCountdownEdit %d ---\n",GPIO_Press_Pin);

  // Если номер редактируемой цифры меньше 2, то правим часы, иначе минуты
  //  static int screen = 0;/
  switch(GPIO_Press_Pin)
  {
  case BTN_LEFT_Pin:
    --editNum;
    if(editNum < 0) editNum = maxNumber;
    break;
  case BTN_RIGHT_Pin:
    ++editNum;
    if(editNum > maxNumber) editNum = 0;
    break;
  case BTN_UP_Pin:
    delta = mult[editNum%2];
    break;
  case BTN_DOWN_Pin:
    delta = -mult[editNum%2];
    break;
  case BTN_MID_Pin:
    screenCur->midPress(NULL);
    break;
  }
//  printf("Time: %02d:%02d, num:%d - edit val: %d\n", sTimeEdit.Hours, sTimeEdit.Minutes, editNum, delta);

  if(editNum<2) //Правим часы
  {
    sCountdownEdit.Hours += delta;
    sCountdownEdit.Hours -= (sCountdownEdit.Hours > 99)?delta:0;
  }
  else if(editNum<4) //Правим минуты
  {
    sCountdownEdit.Minutes += delta;
    sCountdownEdit.Minutes -= (sCountdownEdit.Minutes > maxMinutes)?delta:0;
  }
  else // Правим секунды
  {
    sCountdownEdit.Seconds += delta;
    sCountdownEdit.Seconds -= (sCountdownEdit.Seconds > maxSeconds)?delta:0;
 }

  sprintf(editText, "%02d:%02d:%02d", sCountdownEdit.Hours, sCountdownEdit.Minutes, sCountdownEdit.Seconds);

  uint8_t delimSize = UB_Font_WidthPChar32(':', screenCur->text[0]->font);
  uint8_t digitSize = UB_Font_WidthPChar32('1', screenCur->text[0]->font); // Пока все цифры одной ширины

  textBlink32.x = screenCur->text[0]->x + editNum * digitSize + (editNum/2)*delimSize;
  textBlink32.y = screenCur->text[0]->y;

  printf("Edit num: %d, val %c, ( %d, %d)\n", editNum, editText[editNum], textBlink32.x, textBlink32.y);
  blinkText[0] = editText[editNum + editNum/2];
  blinkText[1] = '\0';
  printf("Blink text: (%s)\n", blinkText);
  editText[editNum + editNum/2] = 127; // Пробел под цифру
  clearScreen();
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
    brightCur += mult[editNum];
    if(brightCur > 255) brightCur -= mult[editNum];
    break;
  case BTN_DOWN_Pin:
    brightCur -= mult[editNum];
    if(brightCur < 0) brightCur += mult[editNum];
    break;
  case BTN_MID_Pin:
    screenCur->midPress(NULL);
    break;
  }
//  brightness
  uint8_t digitSize = UB_Font_WidthPChar32('1', screenCur->text[0]->font); // Пока все цифры одной ширины
  textBlink32.x = textEditBright32.x + (editNum) * digitSize;
  textBlink32.y = textEditBright32.y;

//  illumination =  (3-editNum)*1000 +  textBlink32.x*100 + textBlink32.y;

  sprintf(editText, "%03d", brightCur);
  editText[4]  = '\0';
  blinkText[0] = editText[editNum];
  blinkText[1] = '\0';

  editText[editNum] = 127; // Пробел под цифру

  printf("[%d, %d], %d - '%s'\n",textBlink32.x, textBlink32.y, editNum, editText);

  calcBrightPWM();
  clearScreen();
}


//----------------------------------------------------------------------------------------------------------------------
void clickButton()
{
  haveClick = buttonNoClick;
  screenCur->buttonReceiver();
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
