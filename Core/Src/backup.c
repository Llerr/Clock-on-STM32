/*
 * backup.c
 *
 *  Created on: Jun 30, 2021
 *      Author: lex
 */
#include "backup.h"
#include "rtc.h"
#include "utils.h"
#include "pomidoro.h"

//----------------------------------------------------------------------------------------------------------------------
void saveDateByTimeBKP()
{
  // Раз в день сохраним.
  if( 0 == sTime.Minutes && 0 == sTime.Hours && ( sTime.Seconds < 2 ))
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
  printf("Save alarm1: %02d:%02d, days 0x%02X\n", alarm1.alarmTime.Hours, alarm1.alarmTime.Minutes, alarm1.weekDay);
  printf("Save alarm2: %02d:%02d, days 0x%02X\n", alarm2.alarmTime.Hours, alarm2.alarmTime.Minutes, alarm2.weekDay);
  printf("Save alarm3: %02d:%02d, days 0x%02X\n", alarm3.alarmTime.Hours, alarm3.alarmTime.Minutes, alarm3.weekDay);
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
    for(int i = 0; i < 11; ++i)
      brightnessAll[i] = 1+i*20;
  }
  printf("Load brightness\n");
  for(int i = 0; i < 12; ++i)
    printf(" %d, ", brightnessAll[i]);
  // BKP_DR13
}

//----------------------------------------------------------------------------------------------------------------------
void savePomidoroBKP()
{
  uint32_t saveval = timeToCounter(&sPomidoroWork);
  saveval = (saveval > UINT16_MAX)?UINT16_MAX:saveval;
  printf("Save work time in count: %lu\n", saveval);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR14, saveval);

  saveval = timeToCounter(&sPomidoroSmallRest);
  saveval = (saveval > UINT16_MAX)?UINT16_MAX:saveval;
  printf("Save small rest time in count: %lu\n", saveval);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR15, saveval);

  saveval = timeToCounter(&sPomidoroBigRest);
  saveval = (saveval > UINT16_MAX)?UINT16_MAX:saveval;
  printf("Save big rest time in count: %lu\n", saveval);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR16, saveval);

  saveval = (((uint8_t)numPomidoros) << 8) | (uint8_t)numInSeries;
  printf("Save num pomidoros and series: 0x%lX (%d,%d)\n", saveval, numPomidoros, numInSeries);
  HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR17, saveval);
}

//----------------------------------------------------------------------------------------------------------------------
void loadPomidoroBKP()
{
  uint32_t saveval = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR14);
  printf("Init pomidoro....\n");
  if(saveval != 0) // Если что то сохранено, то будем читать
  {
    timeFromCounter(&sPomidoroWork, saveval);


    saveval = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR15);
    timeFromCounter(&sPomidoroSmallRest, saveval);

    saveval = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR16);
    timeFromCounter(&sPomidoroBigRest, saveval);

    saveval = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR17);
    printf("Num an series 0x%lX\n", saveval);
    numInSeries = saveval&0xFF;
    numPomidoros = (saveval >> 8);
    printf("Load from backup domain\n");
  }
  printf("Work       time: %d:%d:%d\n", sPomidoroWork.Hours, sPomidoroWork.Minutes, sPomidoroWork.Seconds);
  printf("Small rest time: %d:%d:%d\n", sPomidoroSmallRest.Hours, sPomidoroSmallRest.Minutes, sPomidoroSmallRest.Seconds);
  printf("Big rest   time: %d:%d:%d\n", sPomidoroBigRest.Hours, sPomidoroBigRest.Minutes, sPomidoroBigRest.Seconds);
  printf("Num pomidoros in day: %d, num pomidoros in series: %d\n", numPomidoros, numInSeries);

}
