/*
 * buttons.cpp
 *
 *  Created on: Jan 28, 2021
 *      Author: lex
 */

#include <stdio.h>

#include "main.h"
#include "buttons.h"
#include "MatrixRGB.h"
#include "stm32_ub_font.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//  static GPIO_PinState state = GPIO_PIN_RESET;
  printf("Pressed button: %d\n", GPIO_Pin);
  static int x = 0;
  static int y = 0;
  switch(GPIO_Pin)
  {
  case BTN_UP_Pin:
    --x;
    break;
  case BTN_DOWN_Pin:
    ++x;
    break;
  case BTN_LEFT_Pin:
    ++y;
    break;
  case BTN_RIGHT_Pin:
    --y;
    break;
  }
  x = (x<0)?(MATRIX_WIDTH-1):x;
  y = (y<0)?(MATRIX_HEIGHT-1):y;
  if(x > (MATRIX_WIDTH-1))
    x = 0;
  if(y > (MATRIX_HEIGHT-1))
    y = 0;

  clearMatrix();
//  UB_Font_DrawString32(x, y, "12", &Arial_18x27, 7, 0);
//  UB_Font_DrawString(x, y, "1234567890", &Font_4x6, 7, 0);
//  UB_Font_DrawString(x, y+6, "1234567890", &Font_5x8, 7, 0);
//  UB_Font_DrawString(x, y, "1", &Arial_7x10, 7, 0);
//  UB_Font_DrawString(x+7, y, "1", &Arial_8x13, 7, 0);
//  UB_Font_DrawString(x+7+8, y, "1", &Arial_10x15, 7, 0);
//  UB_Font_DrawString(x+25, y, "12", &Arial_11x18, 7, 0);
//  UB_Font_DrawPString(x, y, "12:15", &pComic_16, 7, 0);
  UB_Font_DrawPString(x, y, "$25.2C #36.1% D700", &pLcd_4x6, 7, 0);
  UB_Font_DrawPString(x, y+1, "22:15", &pDigital_7_28, 7, 0);
  UB_Font_DrawPString(x, y+27, "12.06.2021 BT pT @", &pLcd_4x6, 7, 0);
//  printf("[%d,%d]\n",x,y);
//  drawPointT(x, y);
//  testDraw(x, y);
//  updateScreen();
//  dumpScreen();
}
