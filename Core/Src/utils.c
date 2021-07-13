/*
 * utils.c
 *
 *  Created on: Jul 2, 2021
 *      Author: lex
 */
#include <stdint.h>

#include "rtc.h"
#include "Screens.h"
#include "backup.h"
#include "sensors.h"

#include "utils.h"

//------------------------- Будильники ---------------------------------------------------------------------------------
Alarm alarm1 = {0};
Alarm alarm2 = {0};
Alarm alarm3 = {0};
Alarm alarmSleep = {0};
Alarm alarmEdit = {0};

uint8_t alarmOnBit = 7;
uint8_t alarmOnCount = 0;

//------------------ Яркость -------------------------------------------------------------------------------------------
uint8_t brightnessAll[10] = {255};
// Разные линейки применения яркостей
uint16_t illuminationAll[10] = { 300,  600,  1200, 2400, 4800,  7600,  10000, 13000, 16000, 22000};
//uint16_t illuminationAll[10] = {2400, 4900, 7300, 9700, 12100, 14500, 16900, 19300, 21700, 24100};

//----------------------------------------------------------------------------------------------------------------------
void checkDate(RTC_DateTypeDef *date)
{
  uint8_t leapYear = (date->Year%4)?0:1; // Проверка на високосный год
  //Проверим на 0
  if(0 == date->Date)
    date->Date = 1;
  if(0 == date->Month)
    date->Month =1;
  //Проверим на выход за пределы
  switch(date->Month)
  {
  case RTC_MONTH_FEBRUARY:
    date->Date = (date->Date > (28+leapYear))?(28+leapYear):date->Date;
    break;
    // короткие месяцы
  case RTC_MONTH_APRIL:
  case RTC_MONTH_JUNE:
  case RTC_MONTH_SEPTEMBER:
  case RTC_MONTH_NOVEMBER:
    date->Date = (date->Date > 30)?30:date->Date;
    break;
    // длинные месяцы
  case RTC_MONTH_JANUARY:
  case RTC_MONTH_MARCH:
  case RTC_MONTH_MAY:
  case RTC_MONTH_JULY:
  case RTC_MONTH_AUGUST:
  case RTC_MONTH_OCTOBER:
  case RTC_MONTH_DECEMBER:
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t timeIsZero(RTC_TimeTypeDef *time)
{
  return !(time->Seconds|time->Minutes|time->Seconds);
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t decreaseTime(RTC_TimeTypeDef *time)
{
  --time->Seconds;
  if(255 == time->Seconds)
  {
    time->Seconds = 59;
    --time->Minutes;
    if(255 == time->Minutes)
    {
      time->Minutes = 59;
      --time->Hours;
      if(255 == time->Hours)
      {
        time->Seconds = 0;
        time->Minutes = 0;
        time->Hours = 0;
      }
    }
  }
  return timeIsZero(time);
}

//----------------------------------------------------------------------------------------------------------------------
void addTime(RTC_TimeTypeDef *time, uint16_t sec)
{
  uint32_t lineTime =  (uint32_t)(((uint32_t)time->Hours * 3600U) + \
                      ((uint32_t)time->Minutes * 60U) + \
                      ((uint32_t)time->Seconds));

  lineTime += sec;

  time->Hours = (lineTime / 3600U)%24;
  time->Minutes  = (uint8_t)((lineTime % 3600U) / 60U);
  time->Seconds  = (uint8_t)((lineTime % 3600U) % 60U);
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t timeIsEqual(const RTC_TimeTypeDef *time1, const RTC_TimeTypeDef *time2)
{
  // Сначала сравним минуты, они совпадут только 24 раза в сутки.
  return (time1->Minutes == time2->Minutes) && (time1->Hours == time2->Hours) && (time1->Seconds == time2->Seconds);
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t alarmTime(const RTC_TimeTypeDef *alrmTime)
{
  // Сначала сравним минуты, они совпадут только 24 раза в сутки.
  return (sTime.Minutes == alrmTime->Minutes) && (sTime.Hours == alrmTime->Hours) && (sTime.Seconds < 2);
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t alarmCheckDay(Alarm *alrm, WeekDays day)
{
  return alrm->weekDay & (1 << day);
}

//----------------------------------------------------------------------------------------------------------------------
void alarmSetDay(Alarm *alrm, WeekDays day)
{
  alrm->weekDay = alrm->weekDay |  (1 << (uint8_t)day); // Установим флаг
}

//----------------------------------------------------------------------------------------------------------------------
void alarmResetDay(Alarm *alrm, WeekDays day)
{
  alrm->weekDay = alrm->weekDay & ~(1 << (uint8_t)day); // Сбросим флаг
}

//----------------------------------------------------------------------------------------------------------------------
void alarmSetState(Alarm *alrm, uint8_t on)
{
  if(alrm->on != on)
  {
    alrm->on = on;
    alrm->weekDay = alrm->weekDay & ~(1 << alarmOnBit); // Сбросим флаг
    alrm->weekDay = alrm->weekDay |  (on << alarmOnBit); // Установим флаг
  }
  printf("Alarm on: %d, Weekdays alarm 0x%X\n", on, alrm->weekDay);
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t alarmOneShort(Alarm *alrm)
{
  return (1 << alarmOnBit) == alrm->weekDay ;
}

//----------------------------------------------------------------------------------------------------------------------
void alarmOneShortOff(Alarm *alrm)
{
  if(alarmOneShort(alrm))
  {
    alarmSetState(alrm, 0);
    saveAlarmsBKP(); // Сохраним состояние
  }
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t alaramIsOn(Alarm *alrm)
{
  uint8_t ret = 0;
  if(alrm->on) // Если будильник вообще включён
  {
    if(timeIsEqual(&sTime, &alrm->alarmTime))
    {
      if(alarmCheckDay(alrm, sDate.WeekDay) || alarmOneShort(alrm) ) // Срабатывает в этот день или один раз
      {
        ret = 1;
        alarmOneShortOff(alrm); // Выключим одиночный
      }
    }
  }
  return ret;
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t getBrightnessIndex()
{
  uint8_t ret = 0;
  for(ret = 0; ret< 10; ++ret)
  {
    if(illumination < illuminationAll[ret])
    {
//      printf("Illumination: %d, illuminationAll[%d]: %d\n", illumination, ret, illuminationAll[ret]);
      break;
    }
  }
  return ret;
}

