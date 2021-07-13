/*
 * audio.c
 *
 *  Created on: Jul 10, 2021
 *      Author: lex
 */

#include <stdio.h>
#include <stdint.h>


#include "dac.h"
#include "tim.h"

#include "audio.h"

uint8_t playLoop = 0;
TIM_TypeDef *tAudio = NULL;

uint32_t restDataLength = 0;
Audio *trackCur;
const uint16_t *dataCur = NULL;

uint8_t numReadyChanels = 0;

extern DMA_HandleTypeDef hdma_dac_ch1;

//----------------------------------------------------------------------------------------------------------------------
void initAudio()
{
  printf("CPU freq: %ld\n", HAL_RCC_GetSysClockFreq());
  tAudio = TIM6;
//  HAL_DAC_RegisterCallback();
}

//----------------------------------------------------------------------------------------------------------------------
void setFreq(uint32_t freq)
{
  printf("Set frequency: %ld\n", freq);

  uint32_t arr = HAL_RCC_GetSysClockFreq()/freq;
  uint32_t psc = arr/(UINT16_MAX+1);
  arr %= (UINT16_MAX+1);
  printf("Calc psc: %ld, arr: %ld, freq 72MHz/(psc*arr): %ld\n", psc, arr, 72000000/((psc+1)*(arr+1)));
  tAudio->PSC = psc;
  tAudio->ARR = arr;
  tAudio->EGR = TIM_EGR_UG; // установим флаг обновления
}

//----------------------------------------------------------------------------------------------------------------------
void startDAC()
{
  uint32_t length = (restDataLength>UINT16_MAX)?UINT16_MAX:restDataLength;
  printf("Play data length: %ld, pointer %p\n", restDataLength, dataCur);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t *)dataCur, length, DAC_ALIGN_12B_L);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t *)dataCur, length, DAC_ALIGN_12B_L);
  numReadyChanels = 0;
}

//----------------------------------------------------------------------------------------------------------------------
void playSound(Audio *track, uint8_t loop)
{
  playLoop = loop;
  setFreq(track->bitrate);
  HAL_TIM_Base_Start(&htim6);
  trackCur = track;
  restDataLength = trackCur->dataLength;
  dataCur = (uint16_t*)trackCur->data;
  startDAC();
}


//----------------------------------------------------------------------------------------------------------------------
void stopSound()
{
  playLoop = 0;
}

//----------------------------------------------------------------------------------------------------------------------
void continuePlay()
{
  if(2 != numReadyChanels)
  {
    return;
  }

  if(restDataLength < UINT16_MAX) // Уже проиграли всё
  {
    if(playLoop) // Если в цикле, запустим по новой
    {
      printf("Restart play sound.\n");
      restDataLength = trackCur->dataLength;
      dataCur = (uint16_t*)trackCur->data;

      startDAC();
    }
    else // Иначе остановим таймер, всё проиграли
    {
      printf("Stop play sound.\n");
      HAL_TIM_Base_Stop(&htim6);
    }
    return;
  }
  //Уменьшим количество оставшихся данных и сдвинимся  вперёд
  restDataLength -=UINT16_MAX;
  dataCur +=UINT16_MAX;
  startDAC();
}

//----------------------------------------------------------------------------------------------------------------------
void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *inDac)
{
  ++numReadyChanels;
  printf("HAL_DAC_ConvCpltCallbackCh1: %d\n", numReadyChanels);
  continuePlay();
}

//----------------------------------------------------------------------------------------------------------------------
void HAL_DACEx_ConvCpltCallbackCh2(DAC_HandleTypeDef *inDac)
{
  ++numReadyChanels;
  printf("HAL_DACEx_ConvCpltCallbackCh2: %d\n", numReadyChanels);
  continuePlay();
}
//----------------------------------------------------------------------------------------------------------------------

