/*
 * backup.c
 *
 *  Created on: Jun 30, 2021
 *      Author: lex
 */
#include "backup.h"
#include "rtc.h"
#include "utils.h"

//----------------------------------------------------------------------------------------------------------------------
void saveDateByTimeBKP()
{
  // Раз в день сохраним.
  if( 0 == sTime.Hours && 0 == sTime.Minutes && 1 == sTime.Seconds )
  {
    getDate(&sDate);
    printf("Get date: %02d.%02d.%02d\n", sDate.Date, sDate.Month, sDate.Year);
    saveDateBKP(&sDate);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void saveDateBKP(RTC_DateTypeDef *date)
{
  uint16_t saveVal;
  saveVal = date->Date | (date->Month << 8);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, saveVal);
  saveVal = date->Year | (date->WeekDay << 8);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, saveVal);
}

//----------------------------------------------------------------------------------------------------------------------
void loadDateBKP(RTC_DateTypeDef *date)
{
  uint16_t saveVal;
  saveVal = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
  date->Date  = saveVal&0xFF;
  date->Month = saveVal >> 8;

  saveVal = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
  date->Year    = saveVal&0xFF;
  date->WeekDay = saveVal >> 8;
}

//----------------------------------------------------------------------------------------------------------------------
void saveAlarmsBKP()
{
  uint saveVal;
  saveVal = (alarm1.alarmTime.Hours << 8)| alarm1.alarmTime.Minutes;
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, saveVal);

  saveVal = (alarm2.alarmTime.Hours << 8)| alarm2.alarmTime.Minutes;
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, saveVal);

  saveVal = (alarm3.alarmTime.Hours << 8)| alarm3.alarmTime.Minutes;
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR5, saveVal);

  // Дни недели
  saveVal = (alarm1.weekDay << 8) | alarm2.weekDay;
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR6, saveVal);

  saveVal = alarm3.weekDay;
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR7, saveVal);
}

//----------------------------------------------------------------------------------------------------------------------
void loadAlarmsBKP()
{
  uint saveVal;
  saveVal = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
  alarm1.alarmTime.Hours   = saveVal >> 8;
  alarm1.alarmTime.Minutes = saveVal&0xFF;

  saveVal = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
  alarm2.alarmTime.Hours   = saveVal >> 8;
  alarm2.alarmTime.Minutes = saveVal&0xFF;

  saveVal = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5);
  alarm3.alarmTime.Hours   = saveVal >> 8;
  alarm3.alarmTime.Minutes = saveVal&0xFF;

  // Дни недели
  saveVal = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR6);
  alarm1.weekDay = saveVal >> 8;
  alarm2.weekDay = saveVal&0xFF;

  saveVal = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR7);
  alarm3.weekDay = saveVal;

  alarm1.on = (alarm1.weekDay & (1 << alarmOnBit))?1:0;
  alarm2.on = (alarm2.weekDay & (1 << alarmOnBit))?1:0;
  alarm3.on = (alarm3.weekDay & (1 << alarmOnBit))?1:0;
}

