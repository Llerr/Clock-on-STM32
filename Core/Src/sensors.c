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
  BMP280Init(&hi2c1);
  AHT10Init(&hi2c2);
}

void requestDataSensors()
{
  uint8_t haveTemp = 0;
  AHT10RequestData();

  BMP280ReadData();

  if(AHT10Present)
  {
    if(AHT10_Temperature > 13500)
    {
//      AHT10Present = 0; // Если нереальная температура, то скажем, что датчика нет.
      AHT10_Humidity = 11111;
//      return;
    }
    printf("AHT10 have: %d, temp: %d, press: %lu\n", AHT10Present, AHT10_Temperature, AHT10_Humidity);
    if(AHT10_Humidity < 10000) // Если адекватная влажность
      humidity = AHT10_Humidity;
    if(AHT10_Temperature < 13500) // Если адекватная
    {
      temperature = AHT10_Temperature;
      haveTemp = 1;
    }
  }
  if(BMP280Temperature > -30000) //Если пришла температура
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
