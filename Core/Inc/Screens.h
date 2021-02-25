/**
 * @file Screens.h структура экранов и их содержимое
 */
#pragma once

#include <stdint.h>
#include <limits.h>

#define RED     1
#define GREEN   2
#define BLUE    4
#define BLACK   0
#define WHITE   RED|GREEN|BLUE
#define YELLOW  RED|GREEN
#define VIOLET  RED|BLUE
#define MAGENTA GREEN|BLUE


enum ScreensTypeEnum
{
  screenTypeTime,
  screenTypeTimer,
  screenTypeCountDown
};

enum TextTypeEnum
{
  txtTemperature=0, ///< 1 для вывода температуры
  txtHumidity,      ///< 2 для вывода влажности
  txtPressure,      ///< 3 для вывода давления
  txtTime,          ///< 4 для вывода времени
  txtDate,          ///< 5 для вывода даты
  txtAlarm,         ///< 6 для вывода будильниика
  txtTimer,         ///< 7 для вывода секундомера
  txtCountdown,     ///< 8 для вывода таймера
  txtEnumLength
};



typedef struct TextSets_t
{
  int16_t x;
  int16_t y;
  uint8_t color;
  UB_pFont *font;
} TextSets;

/**
 * Структура описания экрана
 */
typedef struct ScreenDescript_t
{
  enum ScreensTypeEnum type; ///< Тип экрана

  TextSets temp; ///< 1 для вывода температуры
  TextSets hum;  ///< 2 для вывода влажности
  TextSets press;     ///< 3 для вывода давления
  TextSets time;      ///< 4 для вывода времени
  TextSets date;      ///< 5 для вывода даты
  TextSets alarm;     ///< 6 для вывода будильниика
  TextSets timer;     ///< 7 для вывода секундомера
  TextSets count;     ///< 8 для вывода таймера
} ScreenDescript;

/**
 * Отрасовка экрана
 */
void drawScreen(ScreenDescript *screen);

extern ScreenDescript mainScreen; ///< Основной экран

