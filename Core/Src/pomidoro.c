/*
 * pomidoro.c
 *
 *  Created on: 2 сент. 2021 г.
 *      Author: lex
 */

#include <stdio.h>
#include <stdint.h>

#include "rtc.h"
#include "utils.h"

RTC_TimeTypeDef sPomidoroCurrent = {0};

RTC_TimeTypeDef sPomidoroWork      = {0, 0, 5}; ///< Время работы
RTC_TimeTypeDef sPomidoroEdit      = {0};
RTC_TimeTypeDef sPomidoroSmallRest = {0, 0,  3}; ///< Время короткого отдыха
RTC_TimeTypeDef sPomidoroBigRest   = {0, 0,  5}; ///< Время большого отдыха

uint8_t pomidoroIsWork = 0;  ///< Помидорный таймер запущен

uint8_t currentPomidoro = 0;      ///< Текущий помидор
uint8_t currentPomidoroIsRest = 0; ///< Текущее время помидора, отдых
uint8_t numPomidoros = 14;        ///< Количество помидоров в день
uint8_t numInSeries  = 4;         ///< Количестов помидоров перед большим перерывом

//----------------------------------------------------------------------------------------------------------------------
void resetPomidoro()
{
  sPomidoroCurrent = sPomidoroWork;
  currentPomidoro = 0;
  currentPomidoroIsRest = 0;
  pomidoroIsWork = 0;
}

//----------------------------------------------------------------------------------------------------------------------
void startStopPomidoror()
{
  pomidoroIsWork = !pomidoroIsWork;
}

//----------------------------------------------------------------------------------------------------------------------
void startPomidoror(RTC_TimeTypeDef *time)
{
  sPomidoroCurrent = *time;
  pomidoroIsWork = 1;
}

//----------------------------------------------------------------------------------------------------------------------
void continuePomidoror()
{
  pomidoroIsWork = 1;
}

//----------------------------------------------------------------------------------------------------------------------
void stopPomidoro()
{
  pomidoroIsWork = 0;
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t pomidoroCountDown()
{

  if(!pomidoroIsWork) // Помидоры не работают
    return 0;
  if(decreaseTime(&sPomidoroCurrent))
  {
    currentPomidoroIsRest = !currentPomidoroIsRest;
    currentPomidoro += !currentPomidoroIsRest;
    printf("Pomidoros: curent: %d, rest: %d\n", currentPomidoro, currentPomidoroIsRest);
    if(currentPomidoroIsRest)
      sPomidoroCurrent = ((currentPomidoro + 1) % numInSeries)?sPomidoroSmallRest:sPomidoroBigRest;
    else
      sPomidoroCurrent = sPomidoroWork;
    if(currentPomidoro == numPomidoros)
    {
      resetPomidoro();
    }

    return 1;
  }
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------
void pomidoroTimerCallBack()
{
    printf("============Alarm event===========\n");
}
