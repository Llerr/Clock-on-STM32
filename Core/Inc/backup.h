/*
 * backup.h
 *
 *  Created on: Jun 30, 2021
 *      Author: lex
 */

#ifndef INC_BACKUP_H_
#define INC_BACKUP_H_

#include "rtc.h"

/**
 * @fn void saveDateByTime()
 * Сохраняет дату в полночь + 1 секунда
 */
void saveDateByTimeBKP();

/**
 * @fn void saveDate(RTC_DateTypeDef*)
 * сохраняет текущую дату в регистрах backup domain
 * @param date дата, которую сохраняем
 */
void saveDateBKP(RTC_DateTypeDef *date);

/**
 * @fn void loadDate(RTC_DateTypeDef*)
 * Считываем текущую дату из регистров backup domain
 * @param date дата, которую сохраняем
 */
void loadDateBKP(RTC_DateTypeDef *date);


#endif /* INC_BACKUP_H_ */
