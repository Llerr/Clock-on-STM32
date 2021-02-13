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

void initSensors()
{
  AHT10Init(&hi2c2);
  BMP280Init(&hi2c1);
}

void requestDataSensors()
{
  AHT10RequestData();
  BMP280ReadData();
}
