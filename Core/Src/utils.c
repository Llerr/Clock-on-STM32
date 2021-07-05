/*
 * utils.c
 *
 *  Created on: Jul 2, 2021
 *      Author: lex
 */
#include <stdint.h>

#include "rtc.h"

#include "utils.h"

Alarm alarm1 = {0};
Alarm alarm2 = {0};
Alarm alarm3 = {0};
Alarm alarmSleep = {0};
Alarm alarmEdit = {0};

uint8_t alarmOnBit = 7;


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
uint8_t timeIsEqual(const RTC_TimeTypeDef *time1, const RTC_TimeTypeDef *time2)
{
  // Сначала сравним минуты, они совпадут только 24 раза в сутки.
  return (time1->Minutes == time2->Minutes) && (time1->Hours == time2->Hours) && (time1->Seconds == time2->Seconds);
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
  alrm->on = on;
  alrm->weekDay = alrm->weekDay & ~(1 << alarmOnBit); // Сбросим флаг
  alrm->weekDay = alrm->weekDay |  (on << alarmOnBit); // Установим флаг
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
    alarmSetState(alrm, 0);
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
      }
    }
  }
  return ret;
}

