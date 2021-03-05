/**
 * @file Screens.h структура экранов и их содержимое
 */
#pragma once

#include <stdint.h>
#include <limits.h>

#include "stm32_ub_font.h"

#define RED     1
#define GREEN   2
#define BLUE    4
#define BLACK   0
#define WHITE   RED|GREEN|BLUE
#define YELLOW  RED|GREEN
#define VIOLET  RED|BLUE
#define MAGENTA GREEN|BLUE
#define TRANSPARENT 8      ///< Прозрачный

#define NUM_MAIN_SCREENS 4

enum StateTypeEnum
{
  stateTime,
  stateTimer,
  stateCountDown,
  stateBrightness,
  stateMenu
};

enum TextTypeEnum
{
  txtTemperature=0, ///< 1  для вывода температуры
  txtHumidity,      ///< 2  для вывода влажности
  txtPressure,      ///< 3  для вывода давления
  txtTime,          ///< 4  для вывода времени
  txtDate,          ///< 5  для вывода даты
  txtAlarm,         ///< 6  для вывода будильниика
  txtTimer,         ///< 7  для вывода секундомера
  txtCountdown,     ///< 8  для вывода таймера
  txtBrightness,    ///< 9  для вывода яркости
  txtText,          ///< 10 для вывода текста
  txtEnumLength
};

extern int stateDev; ///< Текущее состояние
extern int mode;  ///<  Режим состояния

typedef struct TextSets_t
{
  uint8_t type;
  int16_t x;
  int16_t y;
  uint8_t colorFont;
  uint8_t colorBack;
  UB_pFont *font;
  UB_pFont32 *font32;
} TextSets;

/**
 * Структура описания экрана
 */
typedef struct ScreenDescript_t
{
  enum StateTypeEnum type; ///< Тип экрана
  TextSets *blink; ///< Строка для мигания
  uint8_t numText; ///< Количество строк
  TextSets *text[]; ///< Массив строк, для вывода
} ScreenDescript;

/**
 * Отрасовка экрана
 */
void drawScreen();
void setScreenCurent();
void nextScreenMode();
/**
 * Функция переодически рисующая то цветом фона то основным.
 */
void blink();

extern ScreenDescript *screenCur;  ///< Текущий экран

extern ScreenDescript *screenMain[]; ///< Основной экран
extern ScreenDescript screenTimer; ///< Экран секундомера
extern ScreenDescript screenCountdown; ///< Экран счётчика
extern ScreenDescript screenBrightness; ///< Экран яркости
