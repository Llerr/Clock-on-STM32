
#include "stm32_ub_font.h"
#include "MatrixRGB.h"

#include "Screens.h"

void drawScreen(ScreenDescript *screen)
{
  if(screen->temp.font)
  {
    UB_Font_DrawPString(screen->temp.x, screen->temp.y, "$25.2C", screen->temp.font, screen->temp.color );
  }
  if(screen->hum.font)
  {
    UB_Font_DrawPString(screen->hum.x, screen->hum.y, "#36.1%", screen->hum.font, screen->hum.color );
  }
  if(screen->press.font)
  {
    UB_Font_DrawPString(screen->press.x, screen->press.y, "D700", screen->press.font, screen->press.color );
  }
  if(screen->time.font)
  {
    UB_Font_DrawPString(screen->time.x, screen->time.y, "17:24", screen->time.font, screen->time.color );
  }
  if(screen->date.font)
  {
    UB_Font_DrawPString(screen->date.x, screen->date.y, "12.02.2021 BT", screen->date.font, screen->date.color );
  }
  if(screen->alarm.font)
  {
    UB_Font_DrawPString(screen->alarm.x, screen->alarm.y, "@", screen->alarm.font, screen->alarm.color );
  }
  if(screen->timer.font)
  {
    UB_Font_DrawPString(screen->timer.x, screen->timer.y, "", screen->timer.font, screen->timer.color );
  }
  if(screen->count.font)
  {
    UB_Font_DrawPString(screen->count.x, screen->count.y, "", screen->count.font, screen->count.color );
  }
}


ScreenDescript mainScreen =
{
    screenTypeTime,
    // Температура
    {0, 0, RED, &pLcd_4x6},
    //Влажность
    {23, 0, BLUE, &pLcd_4x6},
    //Давление
    {48, 0, MAGENTA, &pLcd_4x6},
    //Время
    {1, 1, WHITE, &pDigital_7_28},
    //Дата
    {1, 27, YELLOW, &pLcd_4x6},
    // Будильник
    {54, 26, VIOLET, &pLcd_4x6},
    //Секундомер
    {0, 0, 4, 0},
    //Таймер
    {0, 0, 4, 0},
};
