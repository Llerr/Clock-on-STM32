/*
 * backup.c
 *
 *  Created on: Jun 30, 2021
 *      Author: lex
 */
#include "backup.h"
#include "rtc.h"

//----------------------------------------------------------------------------------------------------------------------
void saveDateByTimeBKP()
{
  // Раз в день сохраним.
  if( 0 == sTime.Hours && 0 == sTime.Minutes && 1 == sTime.Seconds )
  {
    getDate(&sDate);
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
