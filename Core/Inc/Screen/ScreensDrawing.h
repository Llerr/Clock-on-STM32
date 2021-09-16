/*
 * ScreensDrawing.h
 *
 *  Created on: 11 сент. 2021 г.
 *      Author: lex
 */

#ifndef INC_SCREEN_SCREENSDRAWING_H_
#define INC_SCREEN_SCREENSDRAWING_H_

#include "utils.h"
#include "ScreensDescriptions.h"

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------- Отрисовка текста -------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void drawHour(TextSets *set, void *dataPtr);          // 4 для вывода времени
void drawMinute(TextSets *set, void *dataPtr);          // 4 для вывода времени
void drawBellOn(TextSets *set, void *dataPtr);
void drawDateAdd(TextSets *set, void *dataPtr);          // 5 для вывода даты
void drawTemperature(TextSets *set, void *dataPtr);
void drawHumidity(TextSets *set, void *dataPtr);
void drawPressure(TextSets *set, void *dataPtr);      // 3 для вывода давления
void drawClock(TextSets *set, void *dataPtr);
void drawSleep(TextSets *set, void *dataPtr);
void drawDate(TextSets *set, void *dataPtr);          // 5 для вывода даты
void drawWeekDay(TextSets *set, void *dataPtr);
void drawAlarm(TextSets *set, void *dataPtr);         // 6 для вывода будильниика
void drawBars(Alarm *alrm);
void drawAlarmDays(TextSets *set, void *dataPtr);
void drawAlarmOffDays(TextSets *set, void *dataPtr);
void drawAlarmOn(TextSets *set, void *dataPtr);
void drawTimer(TextSets *set, void *dataPtr);         // 7 для вывода секундомера
void drawCountdown(TextSets *set, void *dataPtr);     // 8 для вывода таймера
void drawBrightness(TextSets *set, void *dataPtr);     // 8 для вывода таймера
void drawIllumination(TextSets *set, void *dataPtr);     // 8 для вывода таймера
void drawPomidoro(TextSets *set, void *dataPtr);
void drawPomidoroInfo(TextSets *set, void *dataPtr);
void drawText(TextSets *set, void *dataPtr);
void drawText32(TextSets *set, void *dataPtr);
void drawMenu(TextSets *set, void *dataPtr);
void drawAHT10(TextSets *set, void *dataPtr);
void drawBMP280(TextSets *set, void *dataPtr);
void drawEdit(TextSets *set, void *dataPtr);
void drawEdit32(TextSets *set, void *dataPtr);
void drawBlink(TextSets *set, void *dataPtr);
void drawBlink32(TextSets *set, void *dataPtr);


#endif /* INC_SCREEN_SCREENSDRAWING_H_ */
