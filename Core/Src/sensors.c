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
#include "sensors.h"

int temperature = -300;
int humidity = -1;
int pressure = -1;

void initSensors()
{
  AHT10Init(&hi2c2);
  BMP280Init(&hi2c1);
}

void requestDataSensors()
{
  uint8_t haveTemp = 0;
  AHT10RequestData();
  BMP280ReadData();

  if(AHT10_Humidity > 0) // Если адекватная влажность
    humidity = AHT10_Humidity;
  if(AHT10_Temperature < 300) // Если адекватная
  {
    temperature = AHT10_Temperature;
    haveTemp = 1;
  }

  if(BMP280Temperature > -300) //Если пришла температура
  {
    if(haveTemp) // Есть на предыдущем шаге
    {
      temperature += BMP280Temperature; //Усредним показания
      temperature /=2;
    }
    else
      temperature = BMP280Temperature;
  }

  if(BMP280Pressure > 0) // Если получили давление
  {
    pressure = BMP280Pressure;
  }
  haveTemp=0;
}
