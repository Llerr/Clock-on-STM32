/**
 * @file Screens.h структура экранов и их содержимое
 */
#pragma once

#include <stdint.h>
#include <limits.h>

#include "MatrixRGB.h"
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

#define NUM_MENU 4 ///< Количество пунктов меню

enum StateTypeEnum
{
  stateTime,
  stateTimer,
  stateCountDown,
  stateBrightness,
//  stateMenu,
  stateMenuTime,
  stateMenuDate,
  stateMenuAlarm,
  stateMenuBrightness,
  stateMenuAlarm1,
  stateMenuAlarm2,
  stateMenuAlarm3,
//  stateMenuAlarm,

  stateTimeEdit,
  stateDateEdtit,
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
  txtMenu,          ///< 11 для вывода меню
  txtMenuSel,          ///< 11 для вывода меню
  txtTimeEdit,
  txtDateEdit,
  txtEnumLength
};

typedef struct TextSets_t
{
  uint8_t type;
  int16_t x;
  int16_t y;
  uint8_t colorFont;
  uint8_t colorBack;
  void *font;
//  UB_pFont32 *font32;
  void (*draw)(struct TextSets_t *set, void *dataPtr); ///< Функция для отрисовки текста
  char *text; ///< Текст для вывода
} TextSets;

/**
 * Структура описания экрана
 */
typedef struct ScreenDescript_t
{
  enum StateTypeEnum type; ///< Тип экрана
  TextSets *blink; ///< Строка для мигания
  struct ScreenDescript_t *nextMode; ///< следующий экран режима
  struct ScreenDescript_t *prevMode; ///< предыдущий экран режима
  struct ScreenDescript_t *nextState; ///< следующий режим
  struct ScreenDescript_t *prevState; ///< предыдущий режим
  struct ScreenDescript_t *backState; ///< режим, при долгом нажатии влево. (выход из меню, из редактирования)

  uint8_t numText; ///< Количество строк
  TextSets *text[]; ///< Массив строк, для вывода
} ScreenDescript;


extern int menu;      ///< Текущий пенкт меню
extern char editMode; ///< Флаг редактирования
extern char blinkText[32]; ///< Текс для мигания
/**
 * Создание структуры окон
 */
void initScreens();

/**
 * Отрасовка экрана
 */
void drawScreen();
void clearScreen();
void nextScreenMode();
/**
 * Функция переодически рисующая то цветом фона то основным.
 */
void blink(uint8_t change);

extern ScreenDescript *screenCur;  ///< Текущий экран

extern TextSets textBlinkTimeEdit;

extern ScreenDescript screenMain1;
extern ScreenDescript screenMain2;
extern ScreenDescript screenMain3;
extern ScreenDescript screenMain4;
extern ScreenDescript screenTimer;
extern ScreenDescript screenCountdown;
extern ScreenDescript screenBrightness;
extern ScreenDescript screenMenu0;
extern ScreenDescript screenMenu1;
extern ScreenDescript screenMenu2;
extern ScreenDescript screenMenu3;
extern ScreenDescript screenMenuAlr0;
extern ScreenDescript screenMenuAlr1;
extern ScreenDescript screenMenuAlr2;

extern ScreenDescript screenEditTime;


//extern ScreenDescript *screenMain[]; ///< Основной экран
//extern ScreenDescript screenTimer; ///< Экран секундомера
//extern ScreenDescript screenCountdown; ///< Экран счётчика
//extern ScreenDescript screenBrightness; ///< Экран яркости
//extern ScreenDescript *screenMenu[]; ///< Экран с меню
