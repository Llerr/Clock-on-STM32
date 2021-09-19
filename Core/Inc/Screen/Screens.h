/**
 * @file Screens.h структура экранов и их содержимое
 */
#pragma once

#include <stdint.h>
#include <limits.h>

#include "MatrixRGB.h"
#include "stm32_ub_font.h"

#include "Screen/ScreensDescriptions.h"
#include "Screen/ScreensDrawing.h"

#define RED     1
#define GREEN   2
#define BLUE    4
#define BLACK   0
#define WHITE   RED|GREEN|BLUE
#define YELLOW  RED|GREEN
#define VIOLET  RED|BLUE
#define MAGENTA GREEN|BLUE
#define TRANSPARENT 8      ///< Прозрачный

#define NUM_MENU 4 ///< Количество пунктов меню


extern int brightCur; ///< Текущая яркость
extern uint8_t counterForScreens; ///< Счётчик для переключения экранов
extern uint8_t resetCounter;      ///< Счётчик для перехода к начальному режиму (Отображение времени)

extern int menu;      ///< Текущий пенкт меню
extern char editMode; ///< Флаг редактирования
extern char editText[32]; ///< Текст для редактирования
extern char editTextDays[32]; ///< Текст для редактирования рабочих дней
extern char editTextOffDays[32]; ///< Текст для редактирования выходных
extern char editTextAlarmOn[32]; ///< Текст для редактирования одиночного будильника

extern char blinkText[32]; ///< Текст для мигания

/**
 * Начальная инициаизация экранов
 */
void initScreens();
///Установка яркости экрана
void setBrightness();

/// Долгое нажатие для отображения меню
//void midStub(int8_t longPress, void *dataPtr);
//void showMenu(int8_t longPress, void *dataPtr);
//void timerStartStop(int8_t longPress, void *dataPtr);
//void countdownStartStop(int8_t longPress, void *dataPtr);
/**
 * Отрасовка экрана
 */
void drawScreen();
void screenSecondCallback();
void clearScreen();
void nextScreenMode();
void drawBars();
/**
 * Функция переодически рисующая то цветом фона то основным.
 */
void blink(uint8_t change);

/**
 * @fn void checkAlarms()
 * Проверка будильников на срабатывание.
 * Если будильник сработал, то добавим к таймеру сна 10 минут.
 */
void checkAlarms();

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void sleepOn();
void alarmOff();
void alarmOn(Alarm *alrm);
void checkAlarms();
void setBrightness();
void initScreens();

//----------------------------------------------------------------------------------------------------------------------
//---------------------------- Нажатие средней кнопки ------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void saveTime(void *dataPtr);
void saveDate(void *dataPtr);
void saveAlarm(void *dataPtr);
void inBrightness(void *dataPtr);       ///< Вход в редактирование яркости
void inCountdownEdit(void *dataPtr);    ///< Вход в редактирование яркости
void countdownStartStop(void *dataPtr);
void pomidoroStartStop(void *dataPtr);
void pomidoroReset(void *dataPtr);
void countdownFinish(void *dataPtr);
void saveCountdown(void *dataPtr);
void saveBrightness(void *dataPtr);
void savePomidoroWork(void *dataPtr);
void savePomidoroSmallRest(void *dataPtr);
void savePomidoroBigRest(void *dataPtr);
void savePomidoroNumInDay(void *dataPtr);
void savePomidoroNumInSeries(void *dataPtr);

void midStub(void *dataPtr);           ///< Заглушка
void selectMenuTime(void *dataPtr);    ///< Редактрование текущего времени (выбор в меню)
void selectMenuAlarm(void *dataPtr);   ///< Редактрование текущего времени (выбор в меню)
void selectMenuDate(void *dataPtr);    ///< Редактрование даты
void selectMenuPomidoroWork(void *dataPtr);
void selectMenuPomidoroSmallRest(void *dataPtr);
void selectMenuPomidoroBigRest(void *dataPtr);
void selectMenuPomidoroNumInDay(void *dataPtr);
void selectMenuPomidoroNumInSeries(void *dataPtr);
void showMenu(void *dataPtr);
void timerStartStop(void *dataPtr);

