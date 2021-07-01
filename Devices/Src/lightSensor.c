/*
 * lightSensor.c
 *
 *  Created on: May 3, 2021
 *      Author: lex
 */
#include <stdio.h>
#include "i2c.h"

#include "lightSensor.h"
#include "sensors.h"

//Время ожидания записи
#define TIME_OUT 1000
/*
 * BIT 7 | BIT 6 | BIT 5 | BIT 4 | BIT 3 | BIT 2 | BIT 1 | BIT 0 | REGISTER ADDRESS
 *  E3   |  E2   |  E1   |  E0   |  M7   |  M6   |  M5   |   M4  |      0x03
 */
#define LUX_HIGH_BYTE_REG 0x03
/*
 * BIT 7 | BIT 6 | BIT 5 | BIT 4 | BIT 3 | BIT 2 | BIT 1 | BIT 0 | REGISTER ADDRESS
 *  --   |  --   |  --   |  --   |  M3   |  M2   |  M1   |   M0  |      0x04
 */
#define LUX_LOW_BYTE_REG  0x04

/// Указатель на канал I2C
I2C_HandleTypeDef *hi2c = NULL;
/// Значение яркости
int brightness = -1;
uint8_t rawValue = 0xFF;

//----------------------------------------------------------------------------------------------------------------------
void MAX44009Init(I2C_HandleTypeDef *hi2cIn)
{
  printf("Start init MAX44009\n");
  hi2c = hi2cIn;
}

//----------------------------------------------------------------------------------------------------------------------
void MAX44009RequestData_IT()
{
//  HAL_I2C_Master_Receive_IT(hi2c, AHT10_ADRESS, (uint8_t*)AHT10_RX_Data, 6);
  printf("Request brightness\n");
  HAL_I2C_Mem_Read_IT(hi2c, MAX44009_READ_ADDR, LUX_HIGH_BYTE_REG, I2C_MEMADD_SIZE_8BIT, &rawValue, 1);

}

//----------------------------------------------------------------------------------------------------------------------
void MAX44009RequestData()
{
  int ret = 0;
  uint8_t exp = 0;
  uint8_t value = 0;
  int ill = 0;
  ret =  HAL_I2C_Mem_Read(hi2c, MAX44009_READ_ADDR, LUX_HIGH_BYTE_REG, I2C_MEMADD_SIZE_8BIT, &rawValue, 1, TIME_OUT);
  switch(ret)
  {
  case HAL_OK:
    exp = rawValue>>4;
    value = rawValue & 0x0F;
    ill = (1<<exp)*value * 72;
    if(ill < 25500) illumination = ill;
//    printf("Brightness %d ( exp:%u, value %u, raw %d)\n", illumination, exp, value, rawValue);
    break;
  case HAL_ERROR:
    printf("HAL_ERROR\n");
    break;
  case HAL_BUSY:
    printf("HAL_BUSY\n");
    break;
  case HAL_TIMEOUT:
    printf("HAL_TIMEOUT\n");
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void MAX44009_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
//  uint8_t rawValue1 = 0xFF;
//  HAL_I2C_Mem_Read(hi2c, READ_ADDR, LUX_LOW_BYTE_REG, I2C_MEMADD_SIZE_8BIT, &rawValue1, 1, TIME_OUT);
  uint8_t exp = rawValue>>4;
  uint8_t value = rawValue & 0x0F;
  int ill = (1<<exp)*value * 72;
  if(ill < 25500) illumination = ill;
//  printf("Brightness %d ( exp:%u, value %u)\n", illumination, exp, value);
}
