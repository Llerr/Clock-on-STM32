/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtc.h
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RTC_H__
#define __RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

extern RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN Private defines */
extern RTC_TimeTypeDef *editTime; ///< Указатель на редактируемую структуру времени
extern RTC_TimeTypeDef sTime;
extern RTC_TimeTypeDef sCountdown;
extern RTC_TimeTypeDef sCountdownEdit;

extern RTC_DateTypeDef sDate;
extern RTC_AlarmTypeDef sAlarm; // структура будильника

extern RTC_TimeTypeDef sTimeEdit; ///< Время для редактирования
extern RTC_DateTypeDef sDateEdit; ///< Дата для редактирования

/* USER CODE END Private defines */

void MX_RTC_Init(void);

/* USER CODE BEGIN Prototypes */
void setTime(RTC_TimeTypeDef *time);
void getTime(RTC_TimeTypeDef *time);
void setDate(RTC_DateTypeDef *date);
void getDate(RTC_DateTypeDef *date);
//void setAlarm(int timer);

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */

