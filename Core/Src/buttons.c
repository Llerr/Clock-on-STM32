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
  drawPoint(x, y);
}
