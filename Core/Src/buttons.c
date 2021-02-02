/*
 * buttons.cpp
 *
 *  Created on: Jan 28, 2021
 *      Author: lex
 */

#include <stdio.h>

#include "buttons.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  printf("Pressed button: %d\n", GPIO_Pin);
}
