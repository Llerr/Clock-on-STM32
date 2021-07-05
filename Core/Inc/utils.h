/*
 * utils.h
 *
 *  Created on: Jul 2, 2021
 *      Author: lex
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include "rtc.h"

typedef struct Alarm_t
{
  RTC_TimeTypeDef alarmTime; ///< Время срабатывания
  uint8_t weekDay;           ///< Битовая маска дней включения будильника (8 бит, разовое включение)
  uint8_t on;                ///< Включён ли будильник
} Alarm;

// Будильники
extern Alarm alarm1;
extern Alarm alarm2;
extern Alarm alarm3;
extern Alarm alarmSleep;
extern Alarm alarmEdit;

typedef enum WeekDays_t
{
  Sunday = 0,
  Monday,
  Tuesday,
  Wednesday,
  Thursday,
  Friday,
  Saturday,
}WeekDays;

extern uint8_t alarmOnBit; ///< 8 бит в маске признак включёного будильника
/**
 * @fn void checkDate(RTC_DateTypeDef*)
 * Проверить дату на корректность, и при её некоректности поправить.
 * @param date Дата для проверки
 */
void checkDate(RTC_DateTypeDef *date);

/**
 * @fn uint8_t timeIsZero(RTC_TimeTypeDef*)
 * Проверка времени на нулевое значение (часы, минуты, секунды равны 0)
 * @param time указатель на структуру времени
 * @return 1 если время нулевое
 */
uint8_t timeIsZero(RTC_TimeTypeDef *time);

/**
 * @fn void decreaseTime(RTC_TimeTypeDef*, uint16_t)
 * Уменьшение времени на val секунд
 * @param time структура времени, время в которой уменьшаем
 * @return 1 если время стало 0
 */
uint8_t decreaseTime(RTC_TimeTypeDef *time);

/**
 * @fn uint8_t timeIsEqual(RTC_TimeTypeDef*, RTC_TimeTypeDef*)
 * Сравнить время
 * @param time1 время для сравнения
 * @param time2 время для сравнения
 * @return 1 если время равно.
 */
uint8_t timeIsEqual(const RTC_TimeTypeDef *time1, const RTC_TimeTypeDef *time2);

/**
 * @fn uint8_t alarmOneShort(Alarm*)
 * Проверка на срабатывание будильника в день недели
 * @param alrm будильник для проверки
 * @return будильник для однократного срабатывания
 */
uint8_t alarmCheckDay(Alarm *alrm, WeekDays day);

void alarmSetDay(Alarm *alrm, WeekDays day);
void alarmResetDay(Alarm *alrm, WeekDays day);
/**
 * @fn void alarmSetState(Alarm*, uint8_t)
 * Включение/отключение бодильника
 * @param alrm будильник
 * @param on признак включения 1, выключения 0
 */
void alarmSetState(Alarm *alrm, uint8_t on);
/**
 * @fn uint8_t alarmOneShort(Alarm*)
 * Проверяем, будильник должен срабатывать 1 раз
 * @param alrm будильник
 * @return 1- будильник должен сработать 0 - нет
 */
uint8_t alarmOneShort(Alarm *alrm);

/**
 * @fn uint8_t alarmOneShort(Alarm*)
 * Отключим будильник, если он одноразовый
 * @param alrm будильник
 */
void alarmOneShortOff(Alarm *alrm);
/**
 * @fn uint8_t alaramIsOn(Alarm*)
 * Пришло время будильника
 * @param arm Будильник, для проверки
 * @return 1 если время срабатывания будильника пришло
 */
uint8_t alaramIsOn(Alarm *alrm);

#endif /* INC_UTILS_H_ */
