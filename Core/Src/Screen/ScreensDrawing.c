/*
 * ScreensDrawing.c
 *
 *  Created on: 11 сент. 2021 г.
 *      Author: lex
 */

#include <stdio.h>

#include "pomidoro.h"
#include "sensors.h"
#include "MatrixRGB.h"
#include "Screen/Screens.h"

//----------------------------------------------------------------------------------------------------------------------
//--------------------------------- Отрисовка текста -------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void drawHour(TextSets *set, void *dataPtr)          // 4 для вывода времени
{
  char buff[32];
  sprintf(buff, "%02d", sTime.Hours);
  setWinBottomRight(26, 21);
  UB_Font_DrawPString16(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
  resetWin();
}

//----------------------------------------------------------------------------------------------------------------------
void drawMinute(TextSets *set, void *dataPtr)          // 4 для вывода времени
{
  char buff[32];
  sprintf(buff, "%02d", sTime.Minutes);
  UB_Font_DrawPString16(set->x, set->y, buff, set->font, set->colorFont, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawBellOn(TextSets *set, void *dataPtr)
{
  if(alarmOnCount)
    drawPicture(set->x, set->y, &picBell);
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
    sprintf(buff, " %d.%d`C      ", temperature / 100, temperature % 100);
  else
    sprintf(buff, " --.--`C        ");
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
    return;
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
    drawBorderRect(x+5*7+1, y-3, x+6*7-1, y-2, RED, RED);
  if(alarmCheckDay(alrm, Sunday))
    drawBorderRect(x+6*7+1, y-3, x+7*7-1, y-2, RED, RED);
  if(alrm->on)
    drawBorderRect(x+7*7+2, y-3, x+9*7-1, y-2, WHITE, WHITE);

//  drawRect(2, 2, 3, 10, RED, BLUE);
  for(uint8_t i = 1; i < 6; ++i)
  {
    if(alarmCheckDay(alrm, i))
      drawBorderRect(x+(i-1)*7+1, y-3, x+i*7-1, y-2, GREEN, GREEN);
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
  sprintf(buff, "%03d", brightCur);
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
void drawPomidoro(TextSets *set, void *dataPtr)
{
  char buff[32];
  sprintf(buff, "%02d:%02d:%02d", sPomidoroCurrent.Hours, sPomidoroCurrent.Minutes, sPomidoroCurrent.Seconds);
  uint8_t color = currentPomidoroIsRest?RED:GREEN;
  UB_Font_DrawPString32(set->x, set->y, buff, set->font, color, set->colorBack);
}

//----------------------------------------------------------------------------------------------------------------------
void drawPomidoroInfo(TextSets *set, void *dataPtr)
{
  char buff[32];
  sprintf(buff, "%02d/%02d", currentPomidoro+1, numPomidoros);
//  uint8_t color = currentPomidoroIsRest?RED:GREEN;
  uint8_t color = set->colorFont;
  UB_Font_DrawPString32(set->x+16, set->y, buff, set->font, color, set->colorBack);

  drawPicture(set->x, set->y, &picPomidoro);
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
void drawAHT10(TextSets *set, void *dataPtr)
{
  char buff[32];
  UB_Font_DrawPString16(0, 0, "AHT10", set->font, set->colorFont, set->colorBack);

  sprintf(buff, " %d.%dC      ", AHT10Temperature / 100, AHT10Temperature % 100);
  UB_Font_DrawPString16(0, 8,  buff, set->font, GREEN, set->colorBack);

  sprintf(buff, " %ld.%ld%%    ", AHT10Humidity/100, AHT10Humidity%100);
  UB_Font_DrawPString16(0, 16, buff, set->font, GREEN, set->colorBack);

}

//----------------------------------------------------------------------------------------------------------------------
void drawBMP280(TextSets *set, void *dataPtr)
{
  char buff[32];
  UB_Font_DrawPString16(0, 0, "BMP280", set->font, set->colorFont, set->colorBack);

  sprintf(buff, " %d.%dC      ", BMP280Temperature/ 100, BMP280Temperature % 100);
  UB_Font_DrawPString16(0, 8, buff, set->font, GREEN, set->colorBack);

  sprintf(buff, " %d.%dmm    ", BMP280Pressure/100, BMP280Pressure%100);
  UB_Font_DrawPString16(0, 16, buff, set->font, GREEN, set->colorBack);

  sprintf(buff, " %d.%d%%    ", BMP280Humidity/100, BMP280Humidity%100);
  UB_Font_DrawPString16(0, 24, buff, set->font, GREEN, set->colorBack);

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

