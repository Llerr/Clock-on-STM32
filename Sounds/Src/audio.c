/*
 * audio.c
 *
 *  Created on: Jul 10, 2021
 *      Author: lex
 */

#include <stdio.h>
#include <stdint.h>

#include "stm32f1xx_hal.h"

#include "audio.h"

uint8_t playLoop = 0;
TIM_TypeDef *tAudio = NULL;

//----------------------------------------------------------------------------------------------------------------------
void initAudio()
{
  printf("CPU freq: %ld\n", HAL_RCC_GetSysClockFreq());
  tAudio = TIM6;
}

//----------------------------------------------------------------------------------------------------------------------
void setFreq(uint32_t freq)
{
  printf("Set frequency: %ld\n", freq);

  uint32_t arr = HAL_RCC_GetSysClockFreq()/freq;
  uint32_t psc = arr/(UINT16_MAX+1);
  arr %= (UINT16_MAX+1);
  tAudio->PSC = psc;
  tAudio->ARR = arr;
  tAudio->EGR = TIM_EGR_UG; // установим флаг обновления
}

//----------------------------------------------------------------------------------------------------------------------
void play(Audio *track, uint8_t loop)
{
  playLoop = loop;
  setFreq(track->bitrate);
}

//----------------------------------------------------------------------------------------------------------------------

