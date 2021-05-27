#include <stdio.h>

#include "stm32_ub_font.h"
#include "MatrixRGB.h"
#include "sensors.h"
#include "buttons.h"
#include "rtc.h"

#include "Screens.h"

#define NUM_MAIN_SCREENS 4


int menu = 0;  ///<  Пункт меню
char editMode = 0; ///< Флаг редактирования
char blinkText[32] = {0};
ScreenDescript *screenCur = NULL;

char *weekText[]=
{
    "Mn ",
    "Tu ",
    "Wd ",
    "Th ",
    "Fr ",
    "St ",
    "Sn ",
};

char *menuText[] =
{
    "Time        ",
    "Date        ",
    "Alarms >    ",
    "Brightness >"
};

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
void drawTemperature(TextSets *set, void *dataPtr)
{
  char buff[32];
  if (temperature > -300)
    sprintf(buff, "T: %d.%dC     ", temperature / 100, temperature % 100);
  else
    sprintf(buff, "T: --.--C       ");

  UB_Font_DrawPString(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawHumidity(TextSets *set, void *dataPtr)
{
  char buff[32];
  if(humidity > 0)
    sprintf(buff, "B: %d.%d%%    ", humidity/100, humidity%100);
  else
    sprintf(buff, "B: --.--%%     ");
  UB_Font_DrawPString(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawPressure(TextSets *set, void *dataPtr)      // 3 для вывода давления
{
  char buff[32];
  if(pressure > 0)
    sprintf(buff, "D: %dmm    ", pressure/100);
  else
    sprintf(buff, "D: ---mm     ");
  UB_Font_DrawPString(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawHour(TextSets *set, void *dataPtr)          // 4 для вывода времени
{
  char buff[32];
  sprintf(buff, "%02d", sTime.Hours);
  UB_Font_DrawPString(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawMinute(TextSets *set, void *dataPtr)          // 4 для вывода времени
{
  char buff[32];
  sprintf(buff, "%02d", sTime.Minutes);
  UB_Font_DrawPString(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawDate(TextSets *set, void *dataPtr)          // 5 для вывода даты
{
  char buff[32];
  sprintf(buff, "%02d.%02d.%02d", sDate.Date, sDate.Month, sDate.Year);
  uint16_t pos = UB_Font_DrawPString(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
  uint8_t colorForWeek;
  if(sDate.WeekDay  > 5)
    colorForWeek = RED;
  else
    colorForWeek = GREEN;
  UB_Font_DrawPString(pos, set->y, weekText[sDate.WeekDay], set->font, colorForWeek, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawAlarm(TextSets *set, void *dataPtr)         // 6 для вывода будильниика
{
//  char buff[32];
  UB_Font_DrawPString(set->x, set->y, "@", set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawTimer(TextSets *set, void *dataPtr)         // 7 для вывода секундомера
{
//  char buff[32];
  UB_Font_DrawPString(set->x, set->y, "000:00.00", set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawCountdown(TextSets *set, void *dataPtr)     // 8 для вывода таймера
{
//  char buff[32];
  UB_Font_DrawPString32(set->x, set->y, "00:00:00", set->font, set->colorFont, set->colorBack);
}
//----------------------------------------------------------------------------------------------------------------------
void drawBrightness(TextSets *set, void *dataPtr)     // 8 для вывода таймера
{
//  char buff[32];
  UB_Font_DrawPString32(set->x, set->y, "00000", set->font, set->colorFont, set->colorBack);
  //      UB_Font_DrawPString(0, 16, "000:00.00", &pComic_16 , 7, 0);
}

//----------------------------------------------------------------------------------------------------------------------
void drawText(TextSets *set, void *dataPtr)
{
//  char buff[32];
  UB_Font_DrawPString(set->x, set->y, set->text, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawMenu(TextSets *set, void *dataPtr)
{
//  char buff[32];
  UB_Font_DrawPString(set->x, set->y, set->text, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawTimeEdit(TextSets *set, void *dataPtr)
{
  char buff[32];
  sprintf(buff, "%02d:%02d", sTimeEdit.Hours, sTimeEdit.Minutes);
  buff[editNum + editNum/2] = 127; // Пробел под цифру
  UB_Font_DrawPString(set->x, set->y, buff, set->font, set->colorFont, TRANSPARENT);
//  blink(0);
}

//----------------------------------------------------------------------------------------------------------------------
void drawBlink(TextSets *set, void *dataPtr)
{
  uint8_t *color = (uint8_t *)(dataPtr);
  UB_Font_DrawPString(set->x, set->y, ":", set->font, *color, TRANSPARENT);
}

//----------------------------------------------------------------------------------------------------------------------
void drawBlinkTimeEdit(TextSets *set, void *dataPtr)
{
  uint8_t *color = (uint8_t *)(dataPtr);
  UB_Font_DrawPString(set->x, set->y, set->text, set->font, *color, TRANSPARENT);
}

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
void clearScreen()
{
  clearMatrix();
}

//----------------------------------------------------------------------------------------------------------------------
void nextScreenMode()
{
//  printf("Next main screen: cur: %p, next: %p\n", screenCur, screenCur->nextMode);
  if(stateTime == screenCur->type)
    screenCur = screenCur->nextMode;
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
//  printf("%lu: Blink, color( %d ) \n", HAL_GetTick(), color);
  screenCur->blink->draw(screenCur->blink, &color);
}

//----------------------------------------------------------------------------------------------------------------------
//                                  1+13*2
TextSets textBlinkTime =   {txtTime, 27,   -5, WHITE, BLACK, &pDigital_7_28, drawBlink, ":"}; // Двоеточие для мигания

TextSets textHour   =        {txtTime,        1, -5, WHITE,  BLACK, &pDigital_7_28, drawHour,        NULL}; // Время
TextSets textMinute =        {txtTime,     27+4, -5, WHITE,  BLACK, &pDigital_7_28, drawMinute,      NULL}; // Время
TextSets textDate =        {txtDate,          0, 21, YELLOW, BLACK, &pArial_13,     drawDate,        NULL}; // Дата
TextSets textTemperature = {txtTemperature,   0, 21, YELLOW, BLACK, &pArial_13,     drawTemperature, NULL}; // температура
TextSets textHumidity =    {txtHumidity,      0, 21, YELLOW, BLACK, &pArial_13,     drawHumidity,    NULL}; // Влажность
TextSets textPressure =    {txtPressure,      0, 21, YELLOW, BLACK, &pArial_13,     drawPressure,    NULL}; // Давление

TextSets textTimer =      {txtTimer,      0, 0, YELLOW, BLACK, &pComic_16, drawTimer,      NULL};
TextSets textCountDown =  {txtCountdown,  0, 0, YELLOW, BLACK, &pTimes_18, drawCountdown,  NULL};
TextSets textBrightness = {txtBrightness, 0, 0, YELLOW, BLACK, &pTimes_18, drawBrightness, NULL};

TextSets textMenuTime      = {txtMenu,    0, 0,  GREEN, BLACK, &pArial_13, drawMenu, "Time       "};
TextSets textMenuTimeSel   = {txtMenuSel, 0, 0,  WHITE, BLACK, &pArial_13, drawMenu, "Time       "};
TextSets textMenuDate      = {txtMenu,    0, 11, GREEN, BLACK, &pArial_13, drawMenu, "Date       "};
TextSets textMenuDateSel   = {txtMenuSel, 0, 11, WHITE, BLACK, &pArial_13, drawMenu, "Date       "};
TextSets textMenuAlr       = {txtMenu,    0, 22, GREEN, BLACK, &pArial_13, drawMenu, "Alarms >   "};
TextSets textMenuAlrSel    = {txtMenuSel, 0, 22, WHITE, BLACK, &pArial_13, drawMenu, "Alarms >   "};
TextSets textMenuBright    = {txtMenu,    0, 0,  GREEN, BLACK, &pArial_13, drawMenu, "Brightness >"};
TextSets textMenuBrightSel = {txtMenuSel, 0, 0,  WHITE, BLACK, &pArial_13, drawMenu, "Brightness >"};

TextSets textMenuAlrm0    = {txtMenu,    0, 0,  GREEN, BLACK, &pArial_13, drawMenu, "Alarms 1     "};
TextSets textMenuAlrm0Sel = {txtMenuSel, 0, 0,  WHITE, BLACK, &pArial_13, drawMenu, "Alarms 1     "};
TextSets textMenuAlrm1    = {txtMenu,    0, 11, GREEN, BLACK, &pArial_13, drawMenu, "Alarms 2     "};
TextSets textMenuAlrm1Sel = {txtMenuSel, 0, 11, WHITE, BLACK, &pArial_13, drawMenu, "Alarms 2     "};
TextSets textMenuAlrm2    = {txtMenu,    0, 22, GREEN, BLACK, &pArial_13, drawMenu, "Alarms 3     "};
TextSets textMenuAlrm2Sel = {txtMenuSel, 0, 22, WHITE, BLACK, &pArial_13, drawMenu, "Alarms 3     "};


TextSets textTimeEdit      = {txtTimeEdit,        1, -5, WHITE,  BLACK, &pDigital_7_28, drawTimeEdit,      NULL}; // Время
TextSets textBlinkTimeEdit = {txtTimeEdit,        1, -5, WHITE,  BLACK, &pDigital_7_28, drawBlinkTimeEdit, blinkText}; // Время


//TextSets *texts = {textTime, textTemperature};
ScreenDescript screenMain1 =
{
    stateTime,
    &textBlinkTime,

    &screenMain2,
    &screenMain4,
    &screenTimer,
    &screenBrightness,
    &screenMain1,
    3,
    {&textHour, &textMinute, &textTemperature}
};

ScreenDescript screenMain2 =
{
    stateTime,
    &textBlinkTime, //blink

    &screenMain3,
    &screenMain1,
    &screenTimer,
    &screenBrightness,
    &screenMain2,
    3,
    {&textHour, &textMinute, &textHumidity}
};

ScreenDescript screenMain3 =
{
    stateTime,
    &textBlinkTime, //blink

    &screenMain4,
    &screenMain2,
    &screenTimer,
    &screenBrightness,
    &screenMain3,
    3,
    {&textHour, &textMinute, &textPressure}
};

ScreenDescript screenMain4 =
{
    stateTime,
    &textBlinkTime, //blink

    &screenMain1,
    &screenMain3,
    &screenTimer,
    &screenBrightness,
    &screenMain4,
    3,
    {&textHour, &textMinute, &textDate}
};

ScreenDescript screenTimer =
{
    stateTimer,
    NULL, //blink

    &screenTimer,
    &screenTimer,
    &screenCountdown,
    &screenMain1,
    &screenMain1,
    1,
    {&textTimer}
};

ScreenDescript screenCountdown =
{
    stateCountDown,
    NULL, //blink

    &screenCountdown,
    &screenCountdown,
    &screenBrightness,
    &screenTimer,
    &screenMain1,
    1,
    {&textCountDown}
};

ScreenDescript screenBrightness =
{
    stateBrightness,
    NULL, //blink

     &screenBrightness,
     &screenBrightness,
     &screenMain1,
     &screenCountdown,
     &screenMain1,
    1,
    {&textBrightness}
};

ScreenDescript screenMenu0 =
{
    stateMenuTime,
    NULL, //blink

    &screenMenu0,
    &screenMenu0,
    &screenMenu0,
    &screenMenu1,
    &screenMain1,
    3,
    {&textMenuTimeSel, &textMenuDate, &textMenuAlr}
};

ScreenDescript screenMenu1 =
{
    stateMenuDate,
    NULL, //blink

    &screenMenu1,
    &screenMenu1,
    &screenMenu0,
    &screenMenu2,
    &screenMain1,
    3,
    {&textMenuTime, &textMenuDateSel, &textMenuAlr}
};

ScreenDescript screenMenu2 =
{
    stateMenuAlarm,
    NULL, //blink

    &screenMenuAlr0,
    &screenMenu2,
    &screenMenu1,
    &screenMenu3,
    &screenMain1,
    3,
    {&textMenuTime, &textMenuDate, &textMenuAlrSel}
};

ScreenDescript screenMenu3 =
{
    stateMenuBrightness,
    NULL, //blink

    &screenMenu3,
    &screenMenu3,
    &screenMenu2,
    &screenMenu3,
    &screenMain1,
    1,
    {&textMenuBrightSel}
};

ScreenDescript screenMenuAlr0 =
{
    stateMenuAlarm,
    NULL, //blink

    &screenMenuAlr0,
    &screenMenu2,
    &screenMenuAlr0,
    &screenMenuAlr1,
    &screenMenu2,
    3,
    {&textMenuAlrm0Sel, &textMenuAlrm1, &textMenuAlrm2}
};

ScreenDescript screenMenuAlr1 =
{
    stateMenuAlarm,
    NULL, //blink

    &screenMenuAlr1,
    &screenMenu2,
    &screenMenuAlr0,
    &screenMenuAlr2,
    &screenMenu2,
    3,
    {&textMenuAlrm0, &textMenuAlrm1Sel, &textMenuAlrm2}
};

ScreenDescript screenMenuAlr2 =
{
    stateMenuAlarm,
    NULL, //blink

    &screenMenuAlr2,
    &screenMenu2,
    &screenMenuAlr1,
    &screenMenuAlr2,
    &screenMenu2,
    3,
    {&textMenuAlrm0, &textMenuAlrm1, &textMenuAlrm2Sel}
};

ScreenDescript screenEditTime =
{
    stateTimeEdit,
    &textBlinkTimeEdit, //blink

    &screenEditTime,
    &screenEditTime,
    &screenEditTime,
    &screenEditTime,
    &screenMenu0,
    1,
    {&textTimeEdit}
};
