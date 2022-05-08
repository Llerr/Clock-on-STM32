/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   This file provides code for the configuration
  *          of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include <string.h>

#include "stm32f1xx_hal_rtc.h"

#include "sensors.h"
#include "Screen/Screens.h"
#include "i2c.h"
#include "main.h"
#include "sensors.h"
#include "backup.h"
#include "utils.h"
#include "pomidoro.h"

RTC_TimeTypeDef *editTime; ///< Указатель на редактируемую структуру времени
RTC_TimeTypeDef sTime = {0};
RTC_TimeTypeDef sCountdown = {0};
RTC_TimeTypeDef sCountdownEdit = {0};


RTC_DateTypeDef sDate = {0};
RTC_AlarmTypeDef sAlarm = {0}; // структура будильника

RTC_TimeTypeDef sTimeEdit; ///< Время для редактирования
RTC_DateTypeDef sDateEdit; ///< Дата для редактирования

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */
#ifdef SET_DATA
  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */
#endif
  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
  //Чтобы не забыть закоментировать установку времени
#ifdef SET_DATA
  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0;
  sTime.Minutes = 0;
  sTime.Seconds = 0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 1;
  DateToUpdate.Year = 0;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
#endif
  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    HAL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    __HAL_RCC_BKP_CLK_ENABLE();
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();

    /* RTC interrupt Init */
    HAL_NVIC_SetPriority(RTC_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_IRQn);
    HAL_NVIC_DisableIRQ(RTC_Alarm_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//----------------------------------------------------------------------------------------------------------------------
void setTime(RTC_TimeTypeDef *time)
{
  HAL_RTC_SetTime(&hrtc, time, RTC_FORMAT_BIN);
}

//----------------------------------------------------------------------------------------------------------------------
void getTime(RTC_TimeTypeDef *time)
{
  HAL_RTC_GetTime(&hrtc, time, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
}

//----------------------------------------------------------------------------------------------------------------------
void setDate(RTC_DateTypeDef *date)
{
  HAL_RTC_SetDate(&hrtc, date, RTC_FORMAT_BIN);
}

//----------------------------------------------------------------------------------------------------------------------
void getDate(RTC_DateTypeDef *date)
{
  HAL_RTC_GetDate(&hrtc, date, RTC_FORMAT_BIN); // RTC_FORMAT_BIN , RTC_FORMAT_BCD
}

//----------------------------------------------------------------------------------------------------------------------
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
//  pomidoroTimerCallBack();
}

//----------------------------------------------------------------------------------------------------------------------
static uint32_t RTC_ReadTimeCounter1(RTC_HandleTypeDef *hrtc)
{
  uint16_t high1 = 0U;
  uint16_t  high2 = 0U;
  uint16_t low = 0U;
  uint32_t timecounter = 0U;

  high1 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);
  low   = READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT);
  high2 = READ_REG(hrtc->Instance->CNTH & RTC_CNTH_RTC_CNT);

  if (high1 != high2)
  {
    /* In this case the counter roll over during reading of CNTL and CNTH registers,
       read again CNTL register then return the counter value */
    timecounter = (((uint32_t) high2 << 16U) | READ_REG(hrtc->Instance->CNTL & RTC_CNTL_RTC_CNT));
  }
  else
  {
    /* No counter roll over during reading of CNTL and CNTH registers, counter
       value is equal to first value of CNTL and CNTH */
    timecounter = (((uint32_t) high1 << 16U) | low);
  }

  return timecounter;
}

//----------------------------------------------------------------------------------------------------------------------
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
//  return;
//  char str[20] = {0};
//  printf("\n------------> Second event\n");
  static uint8_t oldCounter = 0;

  getTime(&sTime);
  uint32_t counter = RTC_ReadTimeCounter1(hrtc);
  // Происходят пропуски и дубдирование времени. Пофиксим
  switch (counter - oldCounter)
  {
  case 0:
    ++counter;
    timeFromCounter(&sTime, counter);
    break;
  case 2:
    --counter;
    timeFromCounter(&sTime, counter);
    break;
  default:
    break;
  }
  oldCounter = counter;

  printf("%02d:%02d:%02d\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
  saveDateByTimeBKP();

  requestDataSensors();

  screenSecondCallback();

  drawScreen();
//  printf("T: %d, H: %d, P: %d\n", temperature, humidity, pressure);
}

/* USER CODE END 1 */
