/*
 * pictures.c
 *
 *  Created on: Jul 1, 2021
 *      Author: lex
 */
#include <stdint.h>

#include "pictures.h"

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const uint8_t CalendarData[] =
{
    7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,0,0,0,0,0,0,0,0,0,0,0,7,
    7,0,0,0,0,0,0,0,0,0,0,0,7,
    7,0,0,0,0,0,0,0,0,0,0,0,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7,
    7,0,0,0,0,0,0,0,0,0,0,0,7,
    7,0,2,0,2,0,2,0,2,0,1,0,7,
    7,0,0,0,0,0,0,0,0,0,0,0,7,
    7,0,2,0,2,0,2,0,2,0,1,0,7,
    7,0,0,0,0,0,0,0,0,0,0,0,7,
    7,0,2,0,2,0,2,0,2,0,1,0,7,
    7,0,0,0,0,0,0,0,0,0,0,0,7,
    7,7,7,7,7,7,7,7,7,7,7,7,7
};

const uint8_t HumidityData[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,7,0,0,0,0,0,0,
    0,0,0,0,0,0,7,0,0,0,0,0,0,
    0,0,0,0,0,7,4,7,0,0,0,0,0,
    0,0,0,0,0,7,4,7,0,0,0,0,0,
    0,0,0,0,7,4,4,4,7,0,0,0,0,
    0,0,0,0,7,4,4,4,7,0,0,0,0,
    0,0,0,0,0,7,7,7,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0
};

const uint8_t PressureData[] =
{
   0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,0,0,7,0,0,0,0,0,7,0,0,7,
   0,0,0,7,0,0,0,0,0,7,0,0,0,
   0,0,7,0,0,0,0,0,7,0,0,7,7,
   0,7,0,0,0,0,0,7,0,0,0,0,0,
   0,7,0,0,0,0,0,7,0,0,0,0,7,
   0,0,7,0,0,0,0,0,7,0,0,0,0,
   0,0,0,7,0,0,0,0,0,7,0,7,7,
   0,0,0,7,0,0,0,0,0,7,0,0,0,
   0,0,7,0,0,0,0,0,7,0,0,0,7,
   7,7,7,7,7,0,7,7,7,7,7,0,0,
   0,7,7,7,0,0,0,7,7,7,0,0,0,
   0,0,7,0,0,0,0,0,7,0,0,0,0
};

const uint8_t TemperatureData[] =
{
    0,0,0,0,7,0,0,0,0,0,0,0,0,
    0,0,0,7,4,7,0,0,0,0,7,0,0,
    0,0,0,7,4,7,0,0,0,7,0,7,0,
    0,0,0,7,4,7,0,0,0,0,7,0,0,
    0,0,0,7,4,7,0,0,0,0,0,0,0,
    0,0,0,7,1,7,0,0,0,0,0,0,0,
    0,0,0,7,1,7,0,0,0,0,0,0,0,
    0,0,0,7,1,7,0,0,0,0,0,0,0,
    0,0,0,7,1,7,0,0,0,0,0,0,0,
    0,0,7,1,1,1,7,0,0,0,0,0,0,
    0,0,7,1,1,1,7,0,0,0,0,0,0,
    0,0,7,1,1,1,7,0,0,0,0,0,0,
    0,0,0,7,7,7,0,0,0,0,0,0,0
};

//----------------------------------------------------------------------------------------------------------------------
Picture picCalendar =
{
    13, 13,
    CalendarData,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picHumidity =
{
    13, 13,
    HumidityData,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picPressure =
{
    13, 13,
    PressureData,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picTemperature =
{
    13, 13,
    TemperatureData,
};

//----------------------------------------------------------------------------------------------------------------------
//------------------------------ ?? ?? ?? ?? ?? ?? ?? / ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? -----------------------------------------------
//----------------------------------------------------------------------------------------------------------------------

const uint8_t illuminationData[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,
    0,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,
    0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,
    0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,
    0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,
    0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,
    0,3,3,3,0,3,0,0,0,0,0,3,0,3,3,3,
    0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,
    0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,
    0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,
    0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,
    0,0,0,3,0,0,0,0,3,0,0,0,0,3,0,0,
    0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0
};

const uint8_t brightnessData[] =
{
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,
    0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,
    0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,
    0,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,
    0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,0,
    0,0,3,3,0,4,0,0,4,7,0,4,0,3,3,0,
    0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,0,
    0,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,
    0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,
    0,0,0,0,3,0,0,4,0,4,0,0,3,0,0,0,
    0,0,0,0,0,0,0,7,7,7,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,7,7,7,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

//----------------------------------------------------------------------------------------------------------------------
Picture picIllumination =
{
    16, 16,
    illuminationData,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picBrightness =
{
    16, 16,
    brightnessData,
};


//----------------------------------------------------------------------------------------------------------------------
//------------------------------ ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? -------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const uint8_t num1Data[] =
{
    0,0,0,7,
    0,0,7,7,
    0,0,0,7,
    0,0,0,7,
    0,0,0,7,
};

//----------------------------------------------------------------------------------------------------------------------
const uint8_t num2Data[] =
{
    7,7,7,7,
    0,0,0,7,
    7,7,7,7,
    7,0,0,0,
    7,7,7,7,
};

//----------------------------------------------------------------------------------------------------------------------
const uint8_t num3Data[] =
{
    7,7,7,7,
    0,0,0,7,
    0,7,7,7,
    0,0,0,7,
    7,7,7,7,
};

//----------------------------------------------------------------------------------------------------------------------
const uint8_t bellData[] =
{
    0,0,0,3,0,0,0,
    0,0,0,3,0,0,0,
    0,0,3,3,3,0,0,
    0,3,7,3,3,3,0,
    0,3,7,3,3,3,0,
    0,3,3,3,3,3,0,
    3,3,3,3,3,3,3,
    0,0,0,7,0,0,0,

};

//----------------------------------------------------------------------------------------------------------------------
Picture picNum1 =
{
    4, 5,
    num1Data,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picNum2 =
{
    4, 5,
    num2Data,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picNum3 =
{
    4, 5,
    num3Data,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picBell =
{
    7, 8,
    bellData,
};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const uint8_t ClockData[] =
{
    0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,3,3,3,0,7,7,7,0,3,3,3,0,0,0,0,0,0,0,0,0,0,
    0,0,7,0,0,0,0,0,3,3,3,7,7,0,0,0,7,7,3,3,3,0,0,0,0,0,7,0,0,0,
    0,7,0,0,7,0,0,0,0,3,7,0,0,0,7,0,0,0,7,3,0,0,0,0,7,0,0,7,0,0,
    0,7,0,7,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,0,7,0,0,7,0,7,0,0,
    7,0,0,7,0,7,0,0,0,7,0,0,0,0,7,0,0,0,0,7,0,0,0,7,0,7,0,0,7,0,
    7,0,0,7,0,7,0,0,0,7,0,0,0,0,7,7,7,0,0,7,0,0,0,7,0,7,0,0,7,0,
    0,7,0,7,0,0,7,0,0,7,0,0,0,0,0,0,0,0,0,7,0,0,7,0,0,7,0,7,0,0,
    0,7,0,0,7,0,0,0,0,0,7,0,0,0,0,0,0,0,7,0,0,0,0,0,7,0,0,7,0,0,
    0,0,7,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,7,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,7,7,0,0,0,7,7,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,7,0,0,7,7,7,0,0,7,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,
};

//----------------------------------------------------------------------------------------------------------------------
const uint8_t SleepData[] =
{
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,
     0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,
     0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,2,2,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,2,0,0,0,0,0,
     0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,2,2,2,2,2,2,2,
     0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,
     0,2,2,2,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,0,0,2,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,
     0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
     2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picClock =
{
  30, 13,
  ClockData,
};

//----------------------------------------------------------------------------------------------------------------------
Picture picSleep =
{
  23, 13,
  SleepData,
};

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const uint8_t PomidoroData[] =
{
         0,0,0,0,0,0,2,0,0,0,0,0,0,0,
         0,0,0,0,0,0,2,0,0,0,0,0,0,0,
         0,0,0,0,0,2,2,2,0,0,0,0,0,0,
         0,0,0,1,2,2,2,2,2,1,0,0,0,0,
         0,0,1,1,2,1,2,2,1,1,1,0,0,0,
         0,1,1,2,1,1,1,2,1,1,1,1,0,0,
         1,1,1,1,1,1,1,1,1,1,1,1,1,0,
         1,1,1,1,1,1,1,1,1,1,1,7,1,1,
         1,1,1,1,1,1,1,1,1,1,1,7,1,1,
         1,1,1,1,1,1,1,1,1,1,1,1,1,0,
         0,1,1,1,1,1,1,1,1,1,1,1,1,0,
         0,1,1,1,1,1,1,1,1,1,1,1,0,0,
         0,0,1,1,1,1,1,1,1,1,1,0,0,0,
         0,0,0,0,1,1,1,1,1,0,0,0,0,0
};

//----------------------------------------------------------------------------------------------------------------------
Picture picPomidoro =
{
  14, 14,
  PomidoroData,
};

