/*
 * sensors.c
 *
 *  Created on: Jan 31, 2021
 *      Author: lex
 */

#include  <stdio.h>

#include "i2c.h"
#include "aht10.h"
#include "bmp280.h"
#include "lightSensor.h"
#include "sensors.h"
#include "utils.h"
#include "Screens.h"

int temperature = -300;
int humidity = -1;
int pressure = -1;
int illumination = 0;

//----------------------------------------------------------------------------------------------------------------------
void initSensors()
{
  BMP280Init(&hi2c1);
  AHT10Init(&hi2c2);
  MAX44009Init(&hi2c1);
}

//----------------------------------------------------------------------------------------------------------------------
void requestDataSensors()
{
  uint8_t haveAT10Data = 0;
  static uint8_t aht10Count = 9;
  //  static uint8_t reset = 0;

  MAX44009RequestData();
  changeBrightness();
  BMP280ReadData();

  //  if(!reset)
  // Опрашиваем не чаще, чем раз в 8 секунд
  // Так рекомендуют.
  if(9 == aht10Count )
  {
    aht10Count = 0;
    AHT10RequestData();
    if(AHT10Present)
      haveAT10Data = 1;
  }
  ++aht10Count;

  if(AHT10Present)
  {
    humidity = AHT10Humidity;
    temperature = AHT10Temperature;
  }

  if(haveAT10Data) // Есть на предыдущем шаге
  {
    temperature +=  BMP280Temperature; //Усредним показания
    temperature /=2;
    humidity += BMP280Humidity;
    humidity /= 2;
  }
  else
  {
    temperature = BMP280Temperature;
    humidity = BMP280Humidity;
  }

  printf("AHT10 have: %d, temp: %d (%d: %d), humidity: %d(%lu: %d)\n", AHT10Present,
      temperature, AHT10Temperature, BMP280Temperature,
      humidity, AHT10Humidity, BMP280Humidity);

  pressure = BMP280Pressure;
}

//----------------------------------------------------------------------------------------------------------------------
void changeBrightness()
{
  uint8_t idx = getBrightnessIndex();
  static uint8_t oldIdx = 0;
  if(oldIdx != idx)
  {
    brightCur = brightnessAll[idx];
    oldIdx = idx;
  }
  calcBrightPWM();
//  printf("Set bright idx: %d, curren bright: %d\n", idx, brightCur);

}

