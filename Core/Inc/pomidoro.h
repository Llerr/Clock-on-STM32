/*
 * pomidoro.h
 *
 *  Created on: 2 сент. 2021 г.
 *      Author: lex
 */

#ifndef INC_POMIDORO_H_
#define INC_POMIDORO_H_

#include "rtc.h"

extern RTC_TimeTypeDef sPomidoroCurrent;    ///< Текущий помидор

extern RTC_TimeTypeDef sPomidoroWork;      ///< Время работы
extern RTC_TimeTypeDef sPomidoroEdit;      ///< Время для редактирования
extern RTC_TimeTypeDef sPomidoroSmallRest; ///< Время короткого перерыва
extern RTC_TimeTypeDef sPomidoroBigRest;   ///< Время длинного перерыва

extern uint8_t pomidoroIsWork;  ///< Помидорный таймер запущен

extern uint8_t currentPomidoro; ///< Текущий помидор
extern uint8_t currentPomidoroIsRest; ///< Текущее время помидора, отдых
extern int numPomidoros;  ///< Количество помидоров в день
extern int numInSeries;   ///< Количестов помидоров перед большим перерывом

/// Сбросить помидоры в начало
/// @note счётчик устанавливается в 0, текщий помидор рабочий
void resetPomidoro();

void startStopPomidoror();
void startPomidoro();
void stopPomidoro();
/// Вычесть время у текущего помиодопа, и переключить при неоходимости
uint8_t pomidoroCountDown();

void pomidoroTimerCallBack();

#endif /* INC_POMIDORO_H_ */
