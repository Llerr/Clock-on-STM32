#include <stdio.h>

#include "stm32_ub_font.h"
#include "MatrixRGB.h"
#include "sensors.h"
#include "buttons.h"
#include "rtc.h"
#include "backup.h"
#include "utils.h"

#include "Screens.h"
#include "pictures.h"

#define NUM_MAIN_SCREENS 4

int curBright = 255; ///< Текущая яркость
uint8_t useCountdown = 0;
uint8_t counterForScreens = 0; ///< счётчик для перехода к следующему экрану
uint8_t resetCounter = 0;      ///< Счётчик для перехода к начальному режиму (Отображение времени)

//int menu = 0;  ///<  Пункт меню
char editMode = 0; ///< Флаг редактирования
char editText[32] = {0};
char editTextDays[32] = {0};
char editTextOffDays[32] = {0};
char editTextAlarmOn[32] = {0};
char blinkText[32] = {0};

ScreenDescript *screenCur = NULL;
ScreenDescript *screenPrev = NULL;

char *weekText[]=
{
    "    Sunday ",
    "    Monday ",
    "  Tuesday ",
    "Wednesday",
    "  Thursday",
    "    Friday ",
    "   Saturday",
};


//Понедельник - Monday - Mon или Mo
//Вторник - Tuesday - Tue или Tu
//Среда - Wednesday - Wed или We
//Четверг - Thursday - Thu или Th
//Пятница - Friday - Fri или Fr
//Суббота - Saturday - Sat или Sa
//Воскресенье - Sunday - Sun или Su


char *menuText[] =
{
    "Time        ",
    "Date        ",
    "Alarms >    ",
    "Brightness >"
};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void drawScreen()
{
  if(!screenCur)
    return;
  //  clearMatrix();
  for(int i = 0; i < screenCur->numText; ++i)
  {
    screenCur->text[i]->draw(screenCur->text[i], NULL);
  }
  //  blink(0); // перересуем соответствующим цветом, то что должно мигать
}

//----------------------------------------------------------------------------------------------------------------------
void screenSecondCallback()
{
  if(useCountdown)
  {
    if(decreaseTime(&sCountdown))
    {
      clearScreen();
      screenCur = &screenCountdownFinish;
      useCountdown = 0;
    }

    return; // Дальше можно ничего не делать
  }

  if(counterForScreens > 3)
  {
    counterForScreens = 0;
    nextScreenMode();
  }
  ++counterForScreens;

}

//----------------------------------------------------------------------------------------------------------------------
void clearScreen()
{
  clearMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void nextScreenMode()
{
  //  printf("Next main screen: cur: %p, next: %p\n", screenCur, screenCur->nextMode);
//  static uint8_t resetCounter = 0;
  switch(screenCur->type)
  {
  // В основном режиме, листаем показания
  case stateTime:
    screenCur = screenCur->nextMode;
    break;
  // В режимах редактирования, ничего не делаем
  case stateAlarmEdit:
  case stateBrightnessEdit:
  case stateCountDownFinish:
  case stateCountDownEdit:
  case stateDateEdtit:
  case stateTimeEdit:
    break;
  // По умолчанию, возвращаемся к показу времени
  default:
    if(++resetCounter > 3)
    {
      clearScreen();
      resetCounter = 0;
      screenCur = &screenMain1;
    }
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void blink(uint8_t change)
{
  if(!screenCur->blink) // Если нет мигания
    return;
  static uint8_t blinkStep = 0;
  static uint8_t color;
  if(change)
  {
    color = (!blinkStep)?screenCur->blink->colorFont:screenCur->blink->colorBack;
    blinkStep = !blinkStep;
  }
  //  screenCur->blink->colorFont = color;
//    printf("%lu: Blink, color( %d ) \n", HAL_GetTick(), color);
  screenCur->blink->draw(screenCur->blink, &color);
}


//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void setBrightness()
{

}

//----------------------------------------------------------------------------------------------------------------------
void initScreens()
{
  screenCur = &screenMain1;

  //   printf("screenMain1: %p\n", &screenMain1);
  //   printf("screenMain2: %p\n", &screenMain2);
  //   printf("screenMain3: %p\n", &screenMain3);
  //   printf("screenMain4: %p\n", &screenMain4);
}

//----------------------------------------------------------------------------------------------------------------------
//---------------------------- Нажатие средней кнопки ------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void saveTime(void *dataPtr)
{
  setTime(&sTimeEdit);
  screenCur = &screenMenuTime;
}

//----------------------------------------------------------------------------------------------------------------------
void saveDate(void *dataPtr)
{
  checkDate(&sDateEdit);
  setDate(&sDateEdit);
  getDate(&sDate);
  saveDateBKP(&sDateEdit);
  screenCur = &screenMenuDate;
}

//----------------------------------------------------------------------------------------------------------------------
void saveAlarm(void *dataPtr)
{
  switch (screenCur->backState->type)
  {
    case stateMenuAlarm1:
      alarm1 = alarmEdit;
      break;
    case stateMenuAlarm2:
      alarm2 = alarmEdit;
      break;
    case stateMenuAlarm3:
      alarm3 = alarmEdit;
      break;
    default:
      break;
  }

  saveAlarmsBKP();
  screenCur = screenCur->backState;
}

//----------------------------------------------------------------------------------------------------------------------
void inBrightness(void *dataPtr) ///< Вход в редактирование яркости
{
  clearMatrix();
  screenBrightnessEdit.backState = screenCur;
  screenCur = &screenBrightnessEdit;

  GPIO_Press_Pin = 0;
  buttonReceiverBrightEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void inCountdownEdit(void *dataPtr) ///< Вход в редактирование яркости
{
  clearMatrix();
  screenCountdownEdit.backState = screenCur;
  screenCur = &screenCountdownEdit;

  GPIO_Press_Pin = 0;
  buttonReceiverCountdownEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void countdownStartStop(void *dataPtr)
{
  if(timeIsZero(&sCountdown)) // Если не установлен счётчик, то ничего не включаем.
  {
//    sCountdown = sCountdownEdit;
    useCountdown = 0;
    return;
  }

  useCountdown = !useCountdown;
  printf("Save count (%02d:%02d:%02d), start: %d\n", sCountdown.Hours, sCountdown.Minutes, sCountdown.Seconds, useCountdown);
}

//----------------------------------------------------------------------------------------------------------------------
void countdownFinish(void *dataPtr)
{
  screenCur = &screenCountdown;
  sCountdown = sCountdownEdit;
}

//----------------------------------------------------------------------------------------------------------------------
void saveCountdown(void *dataPtr)
{
  screenCur = screenCur->backState;
  sCountdown = sCountdownEdit;
  clearScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void saveBrightness(void *dataPtr)
{
  screenCur = screenCur->backState;
  clearScreen();
}

//----------------------------------------------------------------------------------------------------------------------
void midStub(void *dataPtr) ///< Заглушка
{
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuTime(void *dataPtr) ///< Редактрование текущего времени (выбор в меню)
{
  screenCur = &screenEditTime;
  clearScreen();
  GPIO_Press_Pin = 0;
  getTime(&sTimeEdit);
  sTimeEdit.Seconds = 0;
  buttonReceiverTimeEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuAlarm(void *dataPtr) ///< Редактрование текущего времени (выбор в меню)
{
  screenEditAlarm.backState = screenCur;
  screenCur = &screenEditAlarm;
  switch (screenCur->backState->type)
  {
    case stateMenuAlarm1:
      alarmEdit = alarm1;
      break;
    case stateMenuAlarm2:
      alarmEdit = alarm2;
      break;
    case stateMenuAlarm3:
      alarmEdit = alarm3;
      break;
    default:
      break;
  }
  clearScreen();
  GPIO_Press_Pin = 0;
//  getTime(&sTimeEdit);
//  sTimeEdit.Seconds = 0;
  buttonReceiverAlarmEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void selectMenuDate(void *dataPtr) ///< Редактрование текущего времени (выбор в меню)
{
  screenCur = &screenEditDate;
  clearScreen();
  GPIO_Press_Pin = 0;
  getDate(&sDateEdit);
  buttonReceiverDateEdit();
}

//----------------------------------------------------------------------------------------------------------------------
void showMenu(void *dataPtr)
{
//  menu = 0;
  screenCur = &screenMenuTime;
}

//----------------------------------------------------------------------------------------------------------------------
void timerStartStop(void *dataPtr)
{

}

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------- Отрисовка текста -------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void drawHour(TextSets *set, void *dataPtr)          // 4 для вывода времени
{
  char buff[32];
  sprintf(buff, "%02d", sTime.Hours);
  UB_Font_DrawPString16(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawMinute(TextSets *set, void *dataPtr)          // 4 для вывода времени
{
  char buff[32];
  sprintf(buff, "%02d", sTime.Minutes);
  UB_Font_DrawPString16(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawDateAdd(TextSets *set, void *dataPtr)          // 5 для вывода даты
{
  char buff[32];
  sprintf(buff, "   %02d.%02d.%02d   ", sDate.Date, sDate.Month, sDate.Year);
//  drawPicture(set->x, set->y, &picCalendar);
  UB_Font_DrawPString16(set->x /*+ picCalendar.width*/, set->y+2, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawTemperature(TextSets *set, void *dataPtr)
{
  char buff[32];
  if (temperature > -300)
    sprintf(buff, " %d.%dC     ", temperature / 100, temperature % 100);
  else
    sprintf(buff, " --.--C       ");
  drawPicture(set->x, set->y, &picTemperature);
  UB_Font_DrawPString16(set->x + picTemperature.width, set->y + 2, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawHumidity(TextSets *set, void *dataPtr)
{
  char buff[32];
  if(humidity > 0)
    sprintf(buff, " %d.%d%%    ", humidity/100, humidity%100);
  else
    sprintf(buff, " --.--%%     ");
  drawPicture(set->x, set->y, &picHumidity);
  UB_Font_DrawPString16(set->x + picHumidity.width, set->y+2, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawPressure(TextSets *set, void *dataPtr)      // 3 для вывода давления
{
  char buff[32];
  if(pressure > 0)
    sprintf(buff, " %dmm    ", pressure/100);
  else
    sprintf(buff, " ---mm     ");
  drawPicture(set->x, set->y, &picPressure);
  UB_Font_DrawPString16(set->x + picPressure.width, set->y+2, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawClock(TextSets *set, void *dataPtr)
{
  drawPicture(set->x, set->y, &picClock);
}

//----------------------------------------------------------------------------------------------------------------------
void drawSleep(TextSets *set, void *dataPtr)
{
  drawPicture(set->x, set->y, &picSleep);
}

//----------------------------------------------------------------------------------------------------------------------
void drawDate(TextSets *set, void *dataPtr)          // 5 для вывода даты
{
  char buff[32];
  sprintf(buff, "%02d.%02d.%02d", sDate.Date, sDate.Month, sDate.Year);
  UB_Font_DrawPString32(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawWeekDay(TextSets *set, void *dataPtr)
{
  char buff[32];
  sprintf(buff, "%s ", weekText[sDate.WeekDay]);
  set->colorFont = ((sDate.WeekDay  == RTC_WEEKDAY_SATURDAY) || (sDate.WeekDay == RTC_WEEKDAY_SUNDAY))?RED:GREEN;
  UB_Font_DrawPString16(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawAlarm(TextSets *set, void *dataPtr)         // 6 для вывода будильниика
{
  char buff[32];
  Alarm *cur;
  switch(screenCur->type)
  {
  case stateMenuAlarm1:
    cur = &alarm1;
    drawPicture(60, 0, &picNum1);
    break;
  case stateMenuAlarm2:
    cur = &alarm2;
    drawPicture(60, 0, &picNum2);
    break;
  case stateMenuAlarm3:
    cur = &alarm3;
    drawPicture(60, 0, &picNum3);
    break;
  default:
    break;
  }
  drawPicture(57, 5, &picBell);
  sprintf(buff, "%02d:%02d", cur->alarmTime.Hours, cur->alarmTime.Minutes);
  UB_Font_DrawPString16(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);

  drawBars(cur);
}

//----------------------------------------------------------------------------------------------------------------------
void drawBars(Alarm *alrm)
{
  // У экрана будильника 2 надписи Само время (0), список дней (1)
  int x = screenCur->text[1]->x;
  int y = screenCur->text[1]->y;
  if(alarmCheckDay(alrm, Saturday))
    drawRect(x+5*7+1, y-3, x+6*7-1, y-2, RED, RED);
  if(alarmCheckDay(alrm, Sunday))
    drawRect(x+6*7+1, y-3, x+7*7-1, y-2, RED, RED);
  if(alrm->on)
    drawRect(x+7*7+2, y-3, x+9*7-1, y-2, WHITE, WHITE);

//  drawRect(2, 2, 3, 10, RED, BLUE);
  for(uint8_t i = 1; i < 6; ++i)
  {
    if(alarmCheckDay(alrm, i))
      drawRect(x+(i-1)*7+1, y-3, x+i*7-1, y-2, GREEN, GREEN);
  }

}

//----------------------------------------------------------------------------------------------------------------------
//  Понедельник - Monday - Mon или Mo
//  Вторник - Tuesday - Tue или Tu
//  Среда - Wednesday - Wed или We
//  Четверг - Thursday - Thu или Th
//  Пятница - Friday - Fri или Fr
//  Суббота - Saturday - Sat или Sa
//  Воскресенье - Sunday - Sun или Su
void drawAlarmDays(TextSets *set, void *dataPtr)
{
  UB_Font_DrawPString16(set->x,       set->y, "MTWTF", set->font, GREEN, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawAlarmOffDays(TextSets *set, void *dataPtr)
{
  UB_Font_DrawPString16(set->x, set->y,    "SS", set->font,   RED, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawAlarmOn(TextSets *set, void *dataPtr)
{
  UB_Font_DrawPString16(set->x, set->y,     "On", set->font, WHITE, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawTimer(TextSets *set, void *dataPtr)         // 7 для вывода секундомера
{
//  char buff[32];

  UB_Font_DrawPString16(set->x, set->y, "000:00.00", set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawCountdown(TextSets *set, void *dataPtr)     // 8 для вывода таймера
{
  char buff[32];
  sprintf(buff, "%02d:%02d:%02d", sCountdown.Hours, sCountdown.Minutes, sCountdown.Seconds);
  UB_Font_DrawPString32(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawBrightness(TextSets *set, void *dataPtr)     // 8 для вывода таймера
{
  char buff[32];
  sprintf(buff, "%03d", curBright);
  UB_Font_DrawPString32(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
  //      UB_Font_DrawPString(0, 16, "000:00.00", &pComic_16 , 7, 0);
}

//----------------------------------------------------------------------------------------------------------------------
void drawIllumination(TextSets *set, void *dataPtr)     // 8 для вывода таймера
{
  char buff[32];
  sprintf(buff, "%d.%d         ", illumination/100, illumination%100 );
  drawPicture(0, 0,  &picBrightness);
  drawPicture(0, 16, &picIllumination);
  UB_Font_DrawPString16(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
  //      UB_Font_DrawPString(0, 16, "000:00.00", &pComic_16 , 7, 0);
}

//----------------------------------------------------------------------------------------------------------------------
void drawText(TextSets *set, void *dataPtr)
{
  //  char buff[32];
  UB_Font_DrawPString16(set->x, set->y, set->text, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawText32(TextSets *set, void *dataPtr)
{
  //  char buff[32];
  UB_Font_DrawPString32(set->x, set->y, set->text, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawMenu(TextSets *set, void *dataPtr)
{
  //  char buff[32];
  UB_Font_DrawPString16(set->x, set->y, set->text, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawEdit(TextSets *set, void *dataPtr)
{
  UB_Font_DrawPString16(set->x, set->y, set->text, set->font, set->colorFont, TRANSPARENT);
  //  blink(0);
}

//----------------------------------------------------------------------------------------------------------------------
void drawEdit32(TextSets *set, void *dataPtr)
{
  UB_Font_DrawPString32(set->x, set->y, set->text, set->font, set->colorFont, TRANSPARENT);
}

//----------------------------------------------------------------------------------------------------------------------
void drawBlink(TextSets *set, void *dataPtr)
{
  uint8_t *color = (uint8_t *)(dataPtr);
  UB_Font_DrawPString16(set->x, set->y, set->text, set->font, *color, TRANSPARENT);
}

//----------------------------------------------------------------------------------------------------------------------
void drawBlink32(TextSets *set, void *dataPtr)
{
  uint8_t *color = (uint8_t *)(dataPtr);
//  printf("%ld: blink(%s):%d\n", HAL_GetTick(), set->text, *color);
  UB_Font_DrawPString32(set->x, set->y, set->text, set->font, *color, TRANSPARENT);
}

//----------------------------------------------------------------------------------------------------------------------
//---------------------------------- Данные ----------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//                                  1+13*2
TextSets textBlinkTime =   {txtTime, 27,   -5, WHITE, BLACK, &pDigital_7_28, drawBlink, ":"}; // Двоеточие для мигания

TextSets textHour        = {txtTime,        1,    -5,  WHITE, BLACK, &pDigital_7_28, drawHour,         NULL}; // Время
TextSets textMinute      = {txtTime,        27+4, -5,  WHITE, BLACK, &pDigital_7_28, drawMinute,       NULL}; // Время
TextSets textDateAdd     = {txtDate,        0,    19, YELLOW, BLACK, &pArial_13,     drawDateAdd,      NULL}; // Дата дополнительным полем
TextSets textTemperature = {txtTemperature, 0,    19, YELLOW, BLACK, &pArial_13,     drawTemperature,  NULL}; // температура
TextSets textHumidity    = {txtHumidity,    0,    19, YELLOW, BLACK, &pArial_13,     drawHumidity,     NULL}; // Влажность
TextSets textPressure    = {txtPressure,    0,    19, YELLOW, BLACK, &pArial_13,     drawPressure,     NULL}; // Давление
TextSets textClock       = {txtClock,      18,    19, YELLOW, BLACK, &pArial_13,     drawClock,        NULL}; // Будильник
TextSets textSleep       = {txtSleep,      20,    19, YELLOW, BLACK, &pArial_13,     drawSleep,        NULL}; // Досыпание

TextSets textDate        = {txtTimer,       0,     0,  WHITE, BLACK, &pTimes_18,     drawDate,         NULL}; // Дата
TextSets textWeekDay     = {txtTimer,       1,    18, YELLOW, BLACK, &pArial_13,     drawWeekDay,      NULL}; // День недели

TextSets textAlarm            = {txtTime,        0,       -5,  WHITE, BLACK, &pDigital_7_28, drawAlarm,         NULL}; // Время
TextSets textAlarmDays        = {txtAlarmDays,   0,       23, YELLOW, BLACK, &Arial_7x10,    drawAlarmDays,     NULL}; // Список дней недели
TextSets textAlarmOffDays     = {txtAlarmDays,   0+7*5,   23, YELLOW, BLACK, &Arial_7x10,    drawAlarmOffDays,  NULL}; // Список дней недели
TextSets textAlarmOn          = {txtAlarmDays,   0+7*7+1, 23, YELLOW, BLACK, &Arial_7x10,    drawAlarmOn,    NULL}; // Список дней недели
TextSets textAlarmDaysEdit    = {txtAlarmDays,   0,       23, YELLOW, BLACK, &Arial_7x10,    drawEdit,     editTextDays}; // Список дней недели для редактирования
TextSets textAlarmOffDaysEdit = {txtAlarmDays,   0,       23, YELLOW, BLACK, &Arial_7x10,    drawEdit,     editTextOffDays}; // Список дней недели для редактирования
TextSets textAlarmOnEdit      = {txtAlarmDays,   0,       23, YELLOW, BLACK, &Arial_7x10,    drawEdit,     editTextAlarmOn}; // Список дней недели для редактирования
TextSets textBlinkDays        = {txtAlarmDays,   0,       23,  GREEN, BLACK, &Arial_7x10,    drawBlink,     blinkText}; // Рабочий день недели, для мигания
TextSets textBlinkOffDays     = {txtAlarmDays,   0+7*5,   23,    RED, BLACK, &Arial_7x10,    drawBlink,     blinkText}; // Выходной день недели, для мигания
TextSets textBlinkAlarmOn     = {txtAlarmDays,   0+7*7+1, 23,  WHITE, BLACK, &Arial_7x10,    drawBlink,     blinkText}; // Одиночный будильник, для мигания

TextSets textTimer       = {txtTimer,       0,     0, YELLOW, BLACK, &pComic_16,     drawTimer,        NULL};
TextSets textCountDown   = {txtCountdown,   0,     0, YELLOW, BLACK, &pTimes_18,     drawCountdown,    NULL};
TextSets textBrightness  = {txtBrightness, 16,     0, YELLOW, BLACK, &pTimes_18,     drawBrightness,   NULL}; // Яркость экрана
TextSets textIllum       = {txtIllum,      16,    16,    RED, BLACK, &pComic_16,     drawIllumination, NULL}; // Внешняя освещённость

TextSets textCntDownInf     = {txtCountdownInfo,   2, 19,    WHITE, BLACK, &pArial_13,     drawText,    "Countdown"}; // Пояснительная надпись
TextSets textCntDownFinish  = {txtCountdownFinish, 2, 17,      RED, BLACK, &pTimes_18,     drawBlink32,    "FINISH"}; // надпись о завершении отсчёта

/// Пункты меню, выделенные и нет.
TextSets textMenuTime      = {txtMenu,    0, 0,  GREEN, BLACK, &pArial_13, drawMenu, "Time       "};
TextSets textMenuTimeSel   = {txtMenuSel, 0, 0,  WHITE, BLACK, &pArial_13, drawMenu, "Time       "};
TextSets textMenuDate      = {txtMenu,    0, 11, GREEN, BLACK, &pArial_13, drawMenu, "Date       "};
TextSets textMenuDateSel   = {txtMenuSel, 0, 11, WHITE, BLACK, &pArial_13, drawMenu, "Date       "};
TextSets textMenuAlr       = {txtMenu,    0, 22, GREEN, BLACK, &pArial_13, drawMenu, "Alarms >   "};
TextSets textMenuAlrSel    = {txtMenuSel, 0, 22, WHITE, BLACK, &pArial_13, drawMenu, "Alarms >   "};
TextSets textMenuBright    = {txtMenu,    0, 0,  GREEN, BLACK, &pArial_13, drawMenu, "Brightness >"};
TextSets textMenuBrightSel = {txtMenuSel, 0, 0,  WHITE, BLACK, &pArial_13, drawMenu, "Brightness >"};

//TextSets textMenuAlrm0    = {txtMenu,    0, 0,  GREEN, BLACK, &pArial_13, drawMenu, "Alarm 1     "};
//TextSets textMenuAlrm0Sel = {txtMenuSel, 0, 0,  WHITE, BLACK, &pArial_13, drawMenu, "Alarm 1     "};
//TextSets textMenuAlrm1    = {txtMenu,    0, 11, GREEN, BLACK, &pArial_13, drawMenu, "Alarm 2     "};
//TextSets textMenuAlrm1Sel = {txtMenuSel, 0, 11, WHITE, BLACK, &pArial_13, drawMenu, "Alarm 2     "};
//TextSets textMenuAlrm2    = {txtMenu,    0, 22, GREEN, BLACK, &pArial_13, drawMenu, "Alarm 3     "};
//TextSets textMenuAlrm2Sel = {txtMenuSel, 0, 22, WHITE, BLACK, &pArial_13, drawMenu, "Alarm 3     "};


TextSets textTimeEdit      = {txtTimeEdit, 1, -5, WHITE,  BLACK, &pDigital_7_28, drawEdit,  editText};  // Текст для редактирования
TextSets textBlinkTimeEdit = {txtTimeEdit, 1, -5, WHITE,  BLACK, &pDigital_7_28, drawBlink, blinkText}; // Время

TextSets textEditBright32   = {txtEditBright32,  16, 0,  YELLOW, BLACK, &pTimes_18, drawEdit32,    editText};
TextSets textEdit32         = {txtEdit32,         0, 0,  YELLOW, BLACK, &pTimes_18, drawEdit32,    editText};
TextSets textBlink32        = {txtBlink32,        0, 0,  YELLOW, BLACK, &pTimes_18, drawBlink32,   blinkText};


//TextSets *texts = {textTime, textTemperature};
//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMain1 =
{
    stateTime,
    &textBlinkTime,

    &screenMain2,      // следующий экран режима
    &screenMain4,
    &screenDate,
    &screenBrightness,
    &screenMain1,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    showMenu,
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textHour, &textMinute, &textTemperature}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMain2 =
{
    stateTime,
    &textBlinkTime, //blink

    &screenMain3,    // следующий экран режима
    &screenMain1,
    &screenDate,
    &screenBrightness,
    &screenMain2,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    showMenu,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textHour, &textMinute, &textHumidity}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMain3 =
{
    stateTime,
    &textBlinkTime, //Текст для мигания

    &screenMain4,    // следующий экран режима
    &screenMain2,
    &screenDate,
    &screenBrightness,
    &screenMain3,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    showMenu,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textHour, &textMinute, &textPressure}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMain4 =
{
    stateTime,
    &textBlinkTime, //blink

//    &screenClock, // Лево
    &screenMain1, // Лево
    &screenMain3, // Право
    &screenDate,
    &screenBrightness,
    &screenMain4,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    showMenu,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textHour, &textMinute, &textDateAdd}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenClock =
{
    stateTime,
    &textBlinkTime, //blink

    &screenSleep, // Лево
    &screenMain4, // Право
    &screenDate,
    &screenBrightness,
    &screenMain4,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    showMenu,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textHour, &textMinute, &textClock}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenSleep =
{
    stateTime,
    &textBlinkTime, //blink

    &screenMain1, // Лево
    &screenClock, // Право
    &screenDate,
    &screenBrightness,
    &screenMain4,

    &screenMenuTime, // кнопка set

    midStub,      // Краткое нажатие
    showMenu,     // Длинное нажатие
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textHour, &textMinute, &textSleep}
};

//----------------------------------------------------------------------------------------------------------------------
//ScreenDescript screenTimer =
//{
//    stateTimer,
//    NULL, //blink
//
//    &screenTimer,     // следующий экран режима
//    &screenTimer,
//    &screenCountdown,
//    &screenMain1,
//    &screenMain1,

//    &screenMenuTime, // кнопка set

//    midStub,            // Краткое нажатие
//    timerStartStop,     // Длинное нажатие
//    buttonReceiverMenu, // Обработчик кнопок в этом пункте
//    1,
//    {&textTimer}
//};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenDate =
{
    stateCountDown,
    NULL, //blink

    &screenDate,       // следующий экран режима
    &screenDate,       // предыдущий экран режима
    &screenCountdown,  // следующий режим
    &screenMain1,      // предыдущий режим
    &screenMain1,

    &screenMenuTime,   // кнопка set

    midStub,           // Краткое нажатие средней кнопки
    midStub,           // Длинное нажатие средней кнопки

    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    2,
    {&textDate, &textWeekDay}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenCountdown =
{
    stateCountDown,
    NULL, //blink

    &screenCountdown,   // следующий экран режима
    &screenCountdown,   // предыдущий экран режима
    &screenBrightness,  // следующий режим
    &screenDate,       // предыдущий режим
    &screenMain1,

    &screenMenuTime, // кнопка set

    countdownStartStop,   // Краткое нажатие средней кнопки
    inCountdownEdit,              // Длинное нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    2,
    {&textCountDown, &textCntDownInf}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenCountdownFinish =
{
    stateCountDownFinish,
    &textCntDownFinish, //blink

    &screenCountdown,   // следующий экран режима
    &screenCountdown,   // предыдущий экран режима
    &screenCountdown,   // следующий режим
    &screenCountdown,   // предыдущий режим
    &screenMain1,

    &screenMenuTime, // кнопка set

    countdownFinish,   // Краткое нажатие средней кнопки
    inCountdownEdit,              // Длинное нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    1,
    {&textCountDown}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenCountdownEdit =
{
    stateCountDownEdit,
    &textBlink32, //blink

    &screenCountdownEdit,  // следующий экран режима
    &screenCountdownEdit,  // предыдущий экран режима
    &screenCountdownEdit,  // следующий режим
    &screenCountdownEdit,  // предыдущий режим
    &screenMain1,

    &screenCountdownEdit, // кнопка set

    saveCountdown,               // Краткое нажатие средней кнопки
    midStub,                     // Длинное нажатие средней кнопки
    buttonReceiverCountdownEdit, // Обработчик кнопок в этом пункте
    2,
    {&textEdit32, &textCntDownInf}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenBrightness =
{
    stateBrightness,
    NULL, //blink

    &screenBrightness,  // следующий экран режима
    &screenBrightness,  // предыдущий экран режима
    &screenMain1,       // следующий режим
    &screenCountdown,   // предыдущий режим
    &screenMain1,       // режим, при долгом нажатии влево. (выход из меню, из редактирования)

    &screenMenuTime, // кнопка set

    midStub,            // Краткое нажатие средней кнопки
    inBrightness,       // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    2,
    {&textBrightness, &textIllum}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenBrightnessEdit =
{
    stateBrightnessEdit,
    &textBlink32, //blink

    &screenBrightnessEdit,    // следующий экран режима
    &screenBrightnessEdit,    // предыдущий экран режима
    &screenBrightnessEdit,    // следующий режим
    &screenBrightnessEdit,    // предыдущий режим
    &screenBrightness,        // режим, при долгом нажатии влево. (выход из меню, из редактирования)

    &screenBrightnessEdit, // кнопка set (В режиме редактирования не используется)

    saveBrightness,           // Краткое нажатие средней кнопки
    showMenu,                 // Долгое нажатие средней кнопки
    buttonReceiverBrightEdit, // Обработчик кнопок в этом пункте
    2,
    {&textEditBright32, &textIllum}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuTime =
{
    stateMenuTime,
    NULL, //blink

    &screenMenuTime,  // Право
    &screenMain1,  // Лево
    &screenMenuTime,  // вверх
    &screenMenuDate,  // вниз
    &screenMain1,  // Долгое нажатие влево

    &screenMain1, // кнопка set

    selectMenuTime,      // Краткое нажатие центр
    midStub,             // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuTimeSel, &textMenuDate, &textMenuAlr}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuDate =
{
    stateMenuDate,
    NULL, //blink

    &screenMenuDate, // Право
    &screenMenuDate, // Лево
    &screenMenuTime, // вверх
    &screenMenuAlarm, // вниз
    &screenMain1,

    &screenMain1, // кнопка set

    selectMenuDate,   // Краткое нажатие средней кнопки
    midStub,          // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuTime, &textMenuDateSel, &textMenuAlr}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuAlarm =
{
    stateMenuAlarm,
    NULL, //blink

    &screenMenuAlr0,
    &screenMenuAlarm,
    &screenMenuDate,
    &screenMenuBrightness,
    &screenMain1,

    &screenMain1, // кнопка set

    midStub,      // Краткое нажатие средней кнопки
    midStub,      // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    3,
    {&textMenuTime, &textMenuDate, &textMenuAlrSel}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuBrightness =
{
    stateMenuBrightness,
    NULL, //blink

    &screenMenuBrightness,
    &screenMenuBrightness,
    &screenMenuAlarm,
    &screenMenuBrightness,
    &screenMain1,       //Долгое нажатие влево

    &screenMain1, // кнопка set

    inBrightness,      // Краткое нажатие средней кнопки
    midStub,           // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
   1,
    {&textMenuBrightSel}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuAlr0 =
{
    stateMenuAlarm1,
    NULL, //blink

    &screenMenuAlr0,
    &screenMenuAlarm,
    &screenMenuAlr0,
    &screenMenuAlr1,
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuAlarm,      // Краткое нажатие средней кнопки
    midStub,     // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textAlarm, &textAlarmDays, &textAlarmOffDays, &textAlarmOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuAlr1 =
{
    stateMenuAlarm2,
    NULL, //blink

    &screenMenuAlr1,
    &screenMenuAlarm,
    &screenMenuAlr0,
    &screenMenuAlr2,
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuAlarm,      // Краткое нажатие средней кнопки
    midStub,      // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textAlarm, &textAlarmDays, &textAlarmOffDays, &textAlarmOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenMenuAlr2 =
{
    stateMenuAlarm3,
    NULL, //blink

    &screenMenuAlr2,
    &screenMenuAlarm,
    &screenMenuAlr1,
    &screenMenuAlr2,
    &screenMenuAlarm,

    &screenMain1, // кнопка set

    selectMenuAlarm,      // Краткое нажатие средней кнопки
    midStub,      // Долгое нажатие средней кнопки
    buttonReceiverMenu, // Обработчик кнопок в этом пункте
    4,
    {&textAlarm, &textAlarmDays, &textAlarmOffDays, &textAlarmOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenEditTime =
{
    stateTimeEdit,
    &textBlinkTimeEdit, //blink

    &screenEditTime,
    &screenEditTime,
    &screenEditTime,
    &screenEditTime,
    &screenMenuTime,

    &screenEditTime, // кнопка set (В режиме редактирования не используется)

    saveTime,      // Краткое нажатие средней кнопки
    midStub,        // Долгое нажатие средней кнопки
    buttonReceiverTimeEdit, // Обработчик кнопок в этом пункте
    1,
    {&textTimeEdit}
};


//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenEditAlarm =
{
    stateAlarmEdit,
    &textBlinkTimeEdit, //blink

    &screenEditAlarm,
    &screenEditAlarm,
    &screenEditAlarm,
    &screenEditAlarm,
    &screenMenuAlr0,

    &screenEditAlarm, // кнопка set (В режиме редактирования не используется)

    saveAlarm,      // Краткое нажатие средней кнопки
    midStub,        // Долгое нажатие средней кнопки
    buttonReceiverAlarmEdit, // Обработчик кнопок в этом пункте
    4,
    {&textTimeEdit, &textAlarmDays, &textAlarmOffDays, &textAlarmOn}
};

//----------------------------------------------------------------------------------------------------------------------
ScreenDescript screenEditDate =
{
    stateDateEdtit,
    &textBlink32, //blink

    &screenEditDate,
    &screenEditDate,
    &screenEditDate,
    &screenEditDate,
    &screenMenuTime,

    &screenMenuTime, // кнопка set

    saveDate,      // Краткое нажатие средней кнопки
    midStub,      // Долгое нажатие средней кнопки
    buttonReceiverDateEdit, // Обработчик кнопок в этом пункте
    1,
    {&textEdit32}
};

