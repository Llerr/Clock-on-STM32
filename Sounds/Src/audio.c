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

extern DMA_HandleTypeDef hdma_dac_ch1;

//----------------------------------------------------------------------------------------------------------------------
void initAudio()
{
  HAL_StatusTypeDef ret = HAL_OK;
  printf("CPU freq: %ld\n", HAL_RCC_GetSysClockFreq());
  tAudio = TIM6;
//  HAL_DAC_RegisterCallback();
  ret = HAL_DMA_RegisterCallback(&hdma_dac_ch1, HAL_DMA_XFER_CPLT_CB_ID, PlayChannel1Finish);
  printf("HAL_DMA_RegisterCallback ret: %d\n", ret);
  ret = HAL_DMA_RegisterCallback(&hdma_dac_ch1, HAL_DMA_XFER_HALFCPLT_CB_ID, PlayChannel1Half);
  printf("HAL_DMA_RegisterCallback ret: %d\n", ret);
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
void play(Audio *track, uint8_t loop)
{
  playLoop = loop;
  setFreq(track->bitrate);
  uint32_t length = (track->dataLength > 65535)?65535:track->dataLength;
  printf("Play data length: %ld\n", length);
  HAL_TIM_Base_Start(&htim6);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)track->data, track->dataLength, DAC_ALIGN_12B_L);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_2, (uint32_t*)track->data, track->dataLength, DAC_ALIGN_12B_L);
}

//----------------------------------------------------------------------------------------------------------------------
void playBeep()
{

}

//----------------------------------------------------------------------------------------------------------------------
void PlayChannel1Finish(DMA_HandleTypeDef *hdma)
{
  printf("PlayChanel1Finish()\n");
  HAL_TIM_Base_Stop(&htim6);
}

//----------------------------------------------------------------------------------------------------------------------
void PlayChannel1Half(DMA_HandleTypeDef *hdma)
{
  printf("PlayChanel1Finish()\n");
  HAL_TIM_Base_Stop(&htim6);
}

//----------------------------------------------------------------------------------------------------------------------
void PlayChannel2Finish()
{
  printf("PlayChanel2Finish()\n");
//  HAL_TIM_Base_Stop(tAudio);
}

void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);
  printf("HAL_TIMEx_CommutCallback\n");
  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIMEx_CommutCallback could be implemented in the user file
   */
}
/**
  * @brief  Hall commutation changed half complete callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIMEx_CommutHalfCpltCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);
  printf("HAL_TIMEx_CommutHalfCpltCallback\n");
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac)
{
  HAL_TIM_Base_Stop(&htim6);
  printf("HAL_DAC_ConvCpltCallbackCh1\n");
}
//void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim)
//{
//  printf();
//}


//----------------------------------------------------------------------------------------------------------------------

