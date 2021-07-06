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
  stateClock,
  stateSleep,
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

  stateCountDownFinish,

  stateBrightnessEdit,
  stateCountDownEdit,
  stateTimeEdit,
  stateAlarmEdit,
//  stateTimeEdit,
//  stateTimeEdit,
  stateDateEdtit,
};

enum TextTypeEnum
{
  txtTime = 0,          ///< 0  для вывода времени
  txtClock,             ///< 1  для отрисовки часов
  txtSleep,             ///< 2  для отрисовки символа сна
  txtTemperature,       ///< 3  для вывода температуры
  txtHumidity,          ///< 4  для вывода влажности
  txtPressure,          ///< 5  для вывода давления
  txtDateAdd,           ///< 6  для вывода даты дополнительно
  txtAlarm,             ///< 7  для вывода будильниика
  txtDate,              ///< 8  для вывода даты
  txtWeekDay,           ///< 9  для вывода дня недели
  txtTimer,             ///< 10 для вывода секундомера
  txtCountdown,         ///< 11 для вывода таймера
  txtBrightness,        ///< 12 для вывода яркости
  txtIllum,             ///< 13 для значения освещёности
  txtText,              ///< 14 для вывода текста
  txtMenu,              ///< 15 для вывода меню
  txtMenuSel,           ///< 16 для вывода меню
  txtCountdownInfo,     ///< 17 поясняющая надпись таймера
  txtCountdownFinish,   ///< 18 Надпись FINISH для таймера
  txtAlarmDays,
  txtTimeEdit,
  txtDateEdit,
  txtFinish,
  txtEditBright32,
  txtEdit32,
  txtBlink32,
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

  struct ScreenDescript_t *setState; ///< режим при нажатии кнопки set

  /// Функция вызываемая при нажатии средней кнопки
  void (*midPress)(void *dataPtr);
  /// Функция вызываемая при долгом нажатии средней кнопки
  void (*midLongPress)(void *dataPtr);

  void (*buttonReceiver)(); ///< Получатель событий кнопок

  uint8_t numText; ///< Количество строк
  TextSets *text[]; ///< Массив строк, для вывода
} ScreenDescript;

extern int curBright; ///< Текущая яркость
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

extern ScreenDescript *screenCur;  ///< Текущий экран
extern ScreenDescript *screenPrev;  ///< Предыдущий экран

extern TextSets textBrightness;
extern TextSets textBlinkTimeEdit;
extern TextSets textEditBright32;
extern TextSets textEdit32;
extern TextSets textBlink32;
extern TextSets textAlarmDaysBlink;
extern TextSets textBlinkDays; // Рабочий день недели, для мигания
extern TextSets textBlinkOffDays; // Выходной день недели, для мигания
extern TextSets textBlinkAlarmOn; // Одиночный будильник, для мигания

extern ScreenDescript screenMain1;
extern ScreenDescript screenMain2;
extern ScreenDescript screenMain3;
extern ScreenDescript screenMain4;
extern ScreenDescript screenClock;
extern ScreenDescript screenSleep;
extern ScreenDescript screenTimer;
extern ScreenDescript screenDate;
extern ScreenDescript screenCountdown;
extern ScreenDescript screenCountdownFinish;
extern ScreenDescript screenCountdownEdit;
extern ScreenDescript screenBrightness;
extern ScreenDescript screenBrightnessEdit;
extern ScreenDescript screenMenuTime;
extern ScreenDescript screenMenuDate;
extern ScreenDescript screenMenuAlarm;
extern ScreenDescript screenMenuBrightness;
extern ScreenDescript screenMenuAlr0;
extern ScreenDescript screenMenuAlr1;
extern ScreenDescript screenMenuAlr2;

extern ScreenDescript screenEditTime;
extern ScreenDescript screenEditAlarm;
extern ScreenDescript screenEditDate;


//extern ScreenDescript *screenMain[]; ///< Основной экран
//extern ScreenDescript screenTimer; ///< Экран секундомера
//extern ScreenDescript screenCountdown; ///< Экран счётчика
//extern ScreenDescript screenBrightness; ///< Экран яркости
//extern ScreenDescript *screenMenu[]; ///< Экран с меню
