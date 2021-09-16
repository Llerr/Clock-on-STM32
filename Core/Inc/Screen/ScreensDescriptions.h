/*
 * ScreensDescriptions.h
 *
 *  Created on: 11 сент. 2021 г.
 *      Author: lex
 */

#ifndef INC_SCREEN_SCREENSDESCRIPTIONS_H_
#define INC_SCREEN_SCREENSDESCRIPTIONS_H_

enum StateTypeEnum
{
  stateClock,
  stateSleep,

  stateTime,
//  stateTimer,
  stateBrightness,
  stateCountDown,
  stateDate,
  statePomidoro,
//  stateMenu,
  stateMenuTime,
  stateMenuDate,
  stateMenuAlarm,
  stateMenuBrightness,
  stateMenuPomidoro,
  stateMenuDebug,
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
  txtPomidoroWork,
  txtPomidoroRest,
  txtPomidoroInfo,
  txtAlarmDays,
  txtTimeEdit,
  txtDateEdit,
  txtFinish,
  txtEditBright32,
  txtEdit32,
  txtBlink32,
  txtEnumLength,
  txtAHT10,
  txtBMP280,
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
  TextSets *blink;         ///< Строка для мигания
  uint8_t autoReset;       ///< Автоматически выходить из режима
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

extern char *weekText[];

//----------------------------------------------------------------------------------------------------------------------
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

//----------------------------------------------------------------------------------------------------------------------
extern ScreenDescript screenClock;
extern ScreenDescript screenSleep;

extern ScreenDescript screenMain1;
extern ScreenDescript screenMain2;
extern ScreenDescript screenMain3;
extern ScreenDescript screenMain4;
extern ScreenDescript screenDate;
extern ScreenDescript screenCountdown;
extern ScreenDescript screenBrightness;
extern ScreenDescript screenPomidoro;

extern ScreenDescript screenCountdownFinish;
extern ScreenDescript screenCountdownEdit;
extern ScreenDescript screenBrightnessEdit;
extern ScreenDescript screenMenuTime;
extern ScreenDescript screenMenuDate;
extern ScreenDescript screenMenuAlarm;
extern ScreenDescript screenMenuBrightness;
extern ScreenDescript screenMenuAlr0;
extern ScreenDescript screenMenuAlr1;
extern ScreenDescript screenMenuAlr2;
extern ScreenDescript screenMenuDebug;
extern ScreenDescript screenMenuPomidoro;          ///< Общее меню помидора
extern ScreenDescript screenMenuPomidoroWork;      ///< Время работы
extern ScreenDescript screenMenuPomidoroSmallRest; ///< Время короткого перерыва
extern ScreenDescript screenMenuPomidoroBigRest;   ///< Время длинного перерыва
extern ScreenDescript screenMenuPomidorosNum;      ///< Количество помидоров в сутках
extern ScreenDescript screenMenuPomidorosSeries;   ///< Количество помидоров до большого перерыва
extern ScreenDescript screenMenuDebugAHT10;
extern ScreenDescript screenMenuDebugBMP280;


extern ScreenDescript screenEditTime;
extern ScreenDescript screenEditAlarm;
extern ScreenDescript screenEditDate;


//extern ScreenDescript *screenMain[]; ///< Основной экран
//extern ScreenDescript screenTimer; ///< Экран секундомера
//extern ScreenDescript screenCountdown; ///< Экран счётчика
//extern ScreenDescript screenBrightness; ///< Экран яркости
//extern ScreenDescript *screenMenu[]; ///< Экран с меню


#endif /* INC_SCREEN_SCREENSDESCRIPTIONS_H_ */
