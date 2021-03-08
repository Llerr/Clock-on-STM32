/**
  ******************************************************************************
  * @file    rtc.h
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
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
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
extern RTC_AlarmTypeDef sAlarm; // структура будильника

extern RTC_TimeTypeDef sTimeEdit; ///< Время для редактирования
extern RTC_DateTypeDef sDateEdit; ///< Дата для редактирования

extern uint8_t counterForScreens;

/* USER CODE END Private defines */

void MX_RTC_Init(void);

/* USER CODE BEGIN Prototypes */
//void setTime();
//void setDate();
//void setAlarm(int timer);

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc);
void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __RTC_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
