#include <stdio.h>

#include "stm32_ub_font.h"
#include "MatrixRGB.h"
#include "sensors.h"
#include "rtc.h"

#include "Screens.h"

int stateDev = 0; ///< Текущее состояние
int mode = 0;  ///<  Режим состояния
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

//----------------------------------------------------------------------------------------------------------------------
void drawScreen()
{
  if(!screenCur)
    return;
//  clearMatrix();
  char buff[15]; // Буффер для текста
  for(int i = 0; i < screenCur->numText; ++i)
  {
    switch(screenCur->text[i]->type)
    {
    case txtTemperature: // 1 для вывода температуры
      if(temperature > -300)
        sprintf(buff, "T: %d.%dC ", temperature/100, temperature%100);
      else
        sprintf(buff, "T: --.--C    ");
      UB_Font_DrawPString(screenCur->text[i]->x, screenCur->text[i]->y, buff, screenCur->text[i]->font,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
      break;
    case txtHumidity:      // 2 для вывода влажности
      if(humidity > 0)
        sprintf(buff, "B: %d.%d%%    ", humidity/100, humidity%100);
      else
        sprintf(buff, "B: --.--%%     ");
      UB_Font_DrawPString(screenCur->text[i]->x, screenCur->text[i]->y, buff, screenCur->text[i]->font,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
      break;
    case txtPressure:      // 3 для вывода давления
      if(pressure > 0)
        sprintf(buff, "D: %dmm    ", pressure/100);
      else
        sprintf(buff, "D: ---mm     ");
      UB_Font_DrawPString(screenCur->text[i]->x, screenCur->text[i]->y, buff, screenCur->text[i]->font,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
      break;
    case txtTime:          // 4 для вывода времени
      sprintf(buff, "%02d:%02d", sTime.Hours, sTime.Minutes);
      UB_Font_DrawPString(screenCur->text[i]->x, screenCur->text[i]->y, buff, screenCur->text[i]->font,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
      break;
    case txtDate:          // 5 для вывода даты
      sprintf(buff, "%02d.%02d.%02d", sDate.Date, sDate.Month, sDate.Year);
      uint16_t pos = UB_Font_DrawPString(screenCur->text[i]->x, screenCur->text[i]->y, buff, screenCur->text[i]->font,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
      uint8_t colorForWeek;
      if(sDate.WeekDay  > 5)
        colorForWeek = RED;
      else
        colorForWeek = GREEN;
      UB_Font_DrawPString(pos, screenCur->text[i]->y, weekText[sDate.WeekDay], screenCur->text[i]->font,
          colorForWeek, screenCur->text[i]->colorBack);
      break;
    case txtAlarm:         // 6 для вывода будильниика
      UB_Font_DrawPString(screenCur->text[i]->x, screenCur->text[i]->y, "@", screenCur->text[i]->font,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
      break;
    case txtTimer:         // 7 для вывода секундомера
      UB_Font_DrawPString(screenCur->text[i]->x, screenCur->text[i]->y, "000:00.00", screenCur->text[i]->font,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
      break;
    case txtCountdown:     // 8 для вывода таймера
      UB_Font_DrawPString32(screenCur->text[i]->x, screenCur->text[i]->y, "00:00:00", screenCur->text[i]->font32,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
       break;
    case txtBrightness:     // 8 для вывода таймера
      UB_Font_DrawPString32(screenCur->text[i]->x, screenCur->text[i]->y, "12:34:56", screenCur->text[i]->font32,
          screenCur->text[i]->colorFont, screenCur->text[i]->colorBack);
//      UB_Font_DrawPString(0, 16, "000:00.00", &pComic_16 , 7, 0);
     break;
    case txtText:
      break;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
void setScreenCurent()
{
  switch (stateDev)
  {
  case stateTime:
    screenCur = screenMain[mode];
    break;
  case stateTimer:
    screenCur = &screenTimer;
    break;
  case stateCountDown:
    screenCur = &screenCountdown;
    break;
  case stateBrightness:
    screenCur = &screenBrightness;
    break;
  case stateMenu:
    break;
  default:
    break;
  }

}

//----------------------------------------------------------------------------------------------------------------------
void nextScreenMode()
{
  ++mode;
  if(mode < 0) mode = NUM_MAIN_SCREENS-1;
  if((NUM_MAIN_SCREENS-1) < mode) mode = 0;
  setScreenCurent();
}

//----------------------------------------------------------------------------------------------------------------------
void blink()
{
  static uint8_t blinkStep = 0;
  uint8_t color;
  color = (blinkStep)?screenCur->blink->colorFont:screenCur->blink->colorBack;
  switch (screenCur->type)
  {
  case stateTime:
    UB_Font_DrawPString(screenCur->blink->x, screenCur->blink->y, ":", screenCur->blink->font,
              color, TRANSPARENT);
    break;
  case stateTimer:
    break;
  case stateCountDown:
    break;
  case stateBrightness:
    break;
  case stateMenu:
    break;
    default:
      break;
  }
  blinkStep = !blinkStep;
}

TextSets textTime = {txtTime, 1, -5, WHITE, BLACK, &pDigital_7_28, NULL}; // Время
TextSets textBlinkTime = {txtTime, 1+13*2, -5, WHITE, BLACK, &pDigital_7_28, NULL}; // Двоеточие для мигания
TextSets textDate = {txtDate, 0, 21, YELLOW, BLACK, &pArial_13, NULL}; //Дата
TextSets textTemperature = {txtTemperature, 0, 21, YELLOW, BLACK, &pArial_13, NULL}; //Дата
TextSets textHumidity = {txtHumidity, 0, 21, YELLOW, BLACK, &pArial_13, NULL}; //Дата
TextSets textPressure = {txtPressure, 0, 21, YELLOW, BLACK, &pArial_13, NULL}; //Давление

TextSets textTimer = {txtTimer, 0, 0, YELLOW, BLACK, &pComic_16, NULL};
TextSets textCountDown = {txtCountdown, 0, 0, YELLOW, BLACK, &pComic_16, &pTimes_18};
TextSets textBrightness = {txtBrightness, 0, 0, YELLOW, BLACK, NULL, &pTimes_18};

//TextSets *texts = {textTime, textTemperature};

ScreenDescript mainScreen1 =
{
    stateTime,
    &textBlinkTime,
    2,
    {&textTime, &textTemperature}
};

ScreenDescript mainScreen2 =
{
    stateTime,
    &textBlinkTime,
    2,
    {&textTime, &textHumidity}
};

ScreenDescript mainScreen3 =
{
    stateTime,
    &textBlinkTime,
    2,
    {&textTime, &textPressure}
};

ScreenDescript mainScreen4 =
{
    stateTime,
    &textBlinkTime,
    2,
    {&textTime, &textDate}
};

ScreenDescript *screenMain[] =
{
    &mainScreen1, &mainScreen2, &mainScreen3, &mainScreen4
};

ScreenDescript screenTimer =
{
    stateTimer,
    NULL,
    1,
    {&textTimer}
};

ScreenDescript screenCountdown =
{
    stateCountDown,
    NULL,
    1,
    {&textCountDown}
};

ScreenDescript screenBrightness =
{
    stateBrightness,
    NULL,
    1,
    {&textBrightness}
};
