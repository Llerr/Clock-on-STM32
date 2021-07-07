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
  if( 0 == sTime.Minutes && 0 == sTime.Hours && 1 == sTime.Seconds )
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
  printf("Save date: %02d.%02d.%02d\n", date->Date, date->Month, date->Year);
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
  printf("Load date: %02d.%02d.%02d\n", date->Date, date->Month, date->Year);
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

  alarmOnCount = 0;

  alarmOnCount += alarm1.on;
  alarmOnCount += alarm2.on;
  alarmOnCount += alarm3.on;
  printf("Save alarm1: %02d:%02d, days %0x02X\n", alarm1.alarmTime.Hours, alarm1.alarmTime.Minutes, alarm1.weekDay);
  printf("Save alarm2: %02d:%02d, days %0x02X\n", alarm2.alarmTime.Hours, alarm2.alarmTime.Minutes, alarm2.weekDay);
  printf("Save alarm3: %02d:%02d, days %0x02X\n", alarm3.alarmTime.Hours, alarm3.alarmTime.Minutes, alarm3.weekDay);
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

  alarmOnCount = 0;

  alarmOnCount += alarm1.on;
  alarmOnCount += alarm2.on;
  alarmOnCount += alarm3.on;
  printf("Load alarm1: %02d:%02d, days %0x02X\n", alarm1.alarmTime.Hours, alarm1.alarmTime.Minutes, alarm1.weekDay);
  printf("Load alarm2: %02d:%02d, days %0x02X\n", alarm2.alarmTime.Hours, alarm2.alarmTime.Minutes, alarm2.weekDay);
  printf("Load alarm3: %02d:%02d, days %0x02X\n", alarm3.alarmTime.Hours, alarm3.alarmTime.Minutes, alarm3.weekDay);
  // BKP_DR7
}

//----------------------------------------------------------------------------------------------------------------------
void saveBrightnessBKP()
{
  uint16_t *brightVals = (uint16_t *)brightnessAll;
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR8,  brightVals[0]);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR9,  brightVals[1]);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR10, brightVals[2]);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR11, brightVals[3]);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR12, brightVals[4]);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR13, brightVals[5]);
  printf("Save brightness\n");
  // BKP_DR13
}

//----------------------------------------------------------------------------------------------------------------------
void loadBrightnessBKP()
{
  uint16_t *brightVals = (uint16_t *)brightnessAll;
  brightVals[0] = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR8);
  brightVals[1] = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR9);
  brightVals[2] = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR10);
  brightVals[3] = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR11);
  brightVals[4] = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR12);
  brightVals[5] = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR13);
  // Если ничего не сохранено, скорректируем
  if(brightnessAll[0] == 0)
  {
    for(int i = 0; i < 10; ++i)
      brightnessAll[i] = 1+i*25;
  }
  printf("Load brightness\n");
  // BKP_DR13
}

