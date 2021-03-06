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

/**
 * @fn void saveAlarms()
 * Сохранить все будильники в регистрах backup domain
 */
void saveAlarmsBKP();

/**
 * @fn void loadAlarms()
 * Загрузить будильники из регистров backup domain
 */
void loadAlarmsBKP();

/**
 * @fn void saveBrightnessBKP()
 * Сохранить настройки яркости в backup domain
 */
void saveBrightnessBKP();
/**
 * @fn void loadBrightnessBKP()
 * Прочитать настройки яркости из backup domain
 */
void loadBrightnessBKP();
/**
 * @fn void savePomidoro()
 * Сохранить настройки помидорного таймера
 */
void savePomidoroBKP();
/**
 * @fn void loadPomidoro()
 * Прочитать настройки помидорного таймера
 */
void loadPomidoroBKP();

#endif /* INC_BACKUP_H_ */
