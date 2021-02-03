/*
 * bmp280.c
 *
 *  Created on: 3 февр. 2021 г.
 *      Author: lex
 */

#include <stdio.h>

#include "i2c.h"
#include "bmp280.h"

//Адрес устройства на шине i2c
#define BMP280_ADDRESS (0x76<<1) /// BMP280 I2C ADDRES

// Адреса регистров
#define BMP280_REG_ID 0xD0 /// BMP280 ID REGISTER
#define BME280_REG_SOFTRESET 0xE0 /// BMP280 reset register

// Коды команд
#define BME280_SOFTRESET_VALUE 0xB6 //BMP280 SOFT RESET VALUE
#define BMP280_ID 0x58 /// BMP280 I2C ID

I2C_HandleTypeDef *hi2cBMP = NULL;
char BMP280Present = 0;
uint8_t BMP280Id = 0;

//----------------------------------------------------------------------------------------------------------------------
void BMP280Init(I2C_HandleTypeDef *hi2c)
{
  puts("Init BMP280...");
  hi2cBMP = hi2c;
//  HAL_StatusTypeDef status = HAL_OK;
  BMP280Id = BMP280_ReadReg(BMP280_REG_ID);
  printf("ID: 0x%X\n", BMP280Id);

  BMP280_WriteReg(BME280_REG_SOFTRESET,BME280_SOFTRESET_VALUE);
}



//----------------------------------------------------------------------------------------------------------------------
uint8_t BMP280_ReadReg(uint8_t reg)
{
  uint8_t value;
  HAL_I2C_Mem_Read(hi2cBMP, BMP280_ADDRESS, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
void BMP280_WriteReg(uint8_t reg, uint8_t value)
{
  HAL_I2C_Mem_Write(hi2cBMP, BMP280_ADDRESS, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
}

////----------------------------------------------------------------------------------------------------------------------
//static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
//{
//  HAL_StatusTypeDef status = HAL_OK;
//  status = HAL_I2C_Mem_Write(&hi2c1, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x10000);
// if(status != HAL_OK) Error();
//}
//
////----------------------------------------------------------------------------------------------------------------------
//static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)
//{
//  HAL_StatusTypeDef status = HAL_OK;
//  uint8_t value = 0;
//  status = HAL_I2C_Mem_Read(&hi2c1, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x10000);
//  if(status != HAL_OK) Error();
//  return value;
//}
//------------------------------------------------
