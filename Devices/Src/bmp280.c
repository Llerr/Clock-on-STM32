/*
 * bmp280.c
 *
 *  Created on: 3 февр. 2021 г.
 *      Author: lex
 */

#include <stdio.h>

#include "i2c.h"
#include "bmp280.h"

// Адреса регистров
#define BMP280_REG_ID 0xD0 ///< BMP280 ID REGISTER
#define BME280_REG_SOFTRESET 0xE0 ///< BMP280 reset register
#define BME280_REGISTER_STATUS  0XF3 ///< Регистр состояния
#define BME280_REG_CTRL_MEAS 0xF4 ///< Control register pressure and temperature measure
#define BME280_REG_CTRL_HUM 0xF2 // Humidity measure control register
#define BME280_REG_CONFIG 0xF5 ///< Configuration register


// Регистры калибровочных значений
#define BMP280_REG_DIG_T1 0x88
#define BMP280_REG_DIG_T2 0x8A
#define BMP280_REG_DIG_T3 0x8C
#define BMP280_REG_DIG_P1 0x8E
#define BMP280_REG_DIG_P2 0x90
#define BMP280_REG_DIG_P3 0x92
#define BMP280_REG_DIG_P4 0x94
#define BMP280_REG_DIG_P5 0x96
#define BMP280_REG_DIG_P6 0x98
#define BMP280_REG_DIG_P7 0x9A
#define BMP280_REG_DIG_P8 0x9C
#define BMP280_REG_DIG_P9 0x9E

#define BME280_REGISTER_DIG_H1 0xA1
#define BME280_REGISTER_DIG_H2 0xE1
#define BME280_REGISTER_DIG_H3 0xE3
#define BME280_REGISTER_DIG_H4 0xE4
#define BME280_REGISTER_DIG_H5 0xE5
#define BME280_REGISTER_DIG_H6 0xE7

#define BMP280_REG_PRESS_MSB 0xF7



// Настройка оверсемплинга
#define BME280_OSRS_T_SKIP (0x0 << 5)
#define BME280_OSRS_T_x1   (0x1 << 5)
#define BME280_OSRS_T_x2   (0x2 << 5)
#define BME280_OSRS_T_x4   (0x3 << 5)
#define BME280_OSRS_T_x8   (0x4 << 5)
#define BME280_OSRS_T_x16  (0x5 << 5)

#define BME280_OSRS_P_SKIP (0x0 << 2)
#define BME280_OSRS_P_x1   (0x1 << 2)
#define BME280_OSRS_P_x2   (0x2 << 2)
#define BME280_OSRS_P_x4   (0x3 << 2)
#define BME280_OSRS_P_x8   (0x4 << 2)
#define BME280_OSRS_P_x16  (0x5 << 2)

#define BME280_OSRS_H_MSK  0x07
#define BME280_OSRS_H_SKIP 0x00
#define BME280_OSRS_H_x1   0x01
#define BME280_OSRS_H_x2   0x02
#define BME280_OSRS_H_x4   0x03
#define BME280_OSRS_H_x8   0x04
#define BME280_OSRS_H_x16  0x05

// Настройка режима работы
#define BME280_MODE_SLEEP  0x0
#define BME280_MODE_FORCE  0x1
#define BME280_MODE_NORMAL 0x3

//Время ожидания перед замером
#define BME280_STBY_MSK  (0x7 << 5)
#define BME280_STBY_0_5  (0x0 << 5)
#define BME280_STBY_62_5 (0x1 << 5)
#define BME280_STBY_125  (0x2 << 5)
#define BME280_STBY_250  (0x3 << 5)
#define BME280_STBY_500  (0x4 << 5)
#define BME280_STBY_1000 (0x5 << 5)
#define BME280_STBY_2000 (0x6 << 5)
#define BME280_STBY_4000 (0x7 << 5)

// Значение IIR фильтра
#define BME280_FILTER_MSK (0x7 << 2)
#define BME280_FILTER_OFF (0x0 << 2)
#define BME280_FILTER_2   (0x1 << 2)
#define BME280_FILTER_4   (0x2 << 2)
#define BME280_FILTER_8   (0x3 << 2)
#define BME280_FILTER_16  (0x4 << 2)

// Коды команд
#define BME280_SOFTRESET_VALUE 0xB6 //BMP280 SOFT RESET VALUE
//
#define BMP280_ID 0x58 /// BMP280 I2C ID
#define BME280_ID 0x60 /// BME280 I2C ID
#define BME280_STATUS_MEASURING 0X08 //Running conversion
#define BME280_STATUS_IM_UPDATE 0X01 //NVM data copying



//Время ожидания записи
#define TIME_OUT 1000


#define HAVE_BMP_280 1
#define HAVE_BME_280 2

// Структура калибровочных коэффициентов
typedef struct
{
  uint16_t dig_T1;
  int16_t  dig_T2;
  int16_t  dig_T3;

  uint16_t dig_P1;
  int16_t  dig_P2;
  int16_t  dig_P3;
  int16_t  dig_P4;
  int16_t  dig_P5;
  int16_t  dig_P6;
  int16_t  dig_P7;
  int16_t  dig_P8;
  int16_t  dig_P9;
} BMP280_CalibData;

typedef struct
{
  uint8_t dig_H1;
  int16_t dig_H2;
  uint8_t dig_H3;
  int16_t dig_H4;
  int16_t dig_H5;
  int8_t  dig_H6;
} BME280_CalibDataHum;

BMP280_CalibData calibData = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
BME280_CalibDataHum calibDataHum = { -1, -1, -1, -1, -1, -1};
I2C_HandleTypeDef *hi2cBMP = NULL;
char BMP280Present = 0;
uint8_t BMP280Id = 0; ///< Идентификатор модуля
uint8_t BMP280Data[8]; ///< Данные давление и температуры (содержимое регистров)
#define BMP280_DATA_SIZE 6
#define BME280_DATA_SIZE 8

int BMP280Humidity = -30000;    ///< Пересчитаная влажность
int BMP280Temperature = -30000; ///< Пересчитаная температура
int BMP280Pressure = -1;        ///< Пересчитаное давление

uint8_t BMx280_Addr = BMP280_ADDRESS0;
//----------------------------------------------------------------------------------------------------------------------
void BMP280Init(I2C_HandleTypeDef *hi2c)
{
  uint8_t ready = 0xFF;
  puts("Init BMP280...");
  hi2cBMP = hi2c;
Reinit:
//  HAL_StatusTypeDef status = HAL_OK;
  BMP280Id = BMP280_ReadReg(BMP280_REG_ID);
  HAL_Delay(50);
  printf("addr: 0x%X, ID: 0x%X\n", BMx280_Addr>>1, BMP280Id);

  switch (BMP280Id)
  {
    case BMP280_ID:
      BMP280Present = HAVE_BMP_280;
      break;
    case BME280_ID:
      BMP280Present |= HAVE_BME_280;
      break;
    default:
      if(BMP280_ADDRESS0 == BMx280_Addr)
      {
        BMx280_Addr = BMP280_ADDRESS1;
        goto Reinit;
      }
      BMP280Present = 0;
      printf("- BMP280 not found!\n");
      return;
      break;
  }
  printf("+ BMP280 found!\n");
  // Перезапустим
  BMP280_WriteReg(BME280_REG_SOFTRESET,BME280_SOFTRESET_VALUE);
//  dumpCalibration();

  // ждём инициализации датчика (пока скопирутся значения коэффициентов в память)
  do
  {
    ready = BMP280_ReadReg(BME280_REGISTER_STATUS);
  }
  while(ready&BME280_STATUS_IM_UPDATE);
  // Прочтём все регистры калибровки
  HAL_I2C_Mem_Read(hi2cBMP, BMx280_Addr, BMP280_REG_DIG_T1, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&calibData), sizeof(calibData), TIME_OUT);
  if(HAVE_BME_280 & BMP280Present)
  {
    calibDataHum.dig_H1 = BMP280_ReadReg(BME280_REGISTER_DIG_H1);
//    HAL_I2C_Mem_Read(hi2cBMP, BMx280_Addr, BME280_REGISTER_DIG_H2, I2C_MEMADD_SIZE_8BIT,
//        (uint8_t*)(&calibDataHum.dig_H2), sizeof(BME280_REGISTER_DIG_H2) - 1, TIME_OUT);
    calibDataHum.dig_H2 = BMP280_ReadReg_I16(BME280_REGISTER_DIG_H2);
    calibDataHum.dig_H3 = BMP280_ReadReg(BME280_REGISTER_DIG_H3);
    calibDataHum.dig_H4 = (BMP280_ReadReg(BME280_REGISTER_DIG_H4) << 4) |
                          (BMP280_ReadReg(BME280_REGISTER_DIG_H4+1) & 0xF);
    calibDataHum.dig_H5 = (BMP280_ReadReg(BME280_REGISTER_DIG_H5+1) << 4) |
                          (BMP280_ReadReg(BME280_REGISTER_DIG_H5) >> 4);
    calibDataHum.dig_H6 = (int8_t)BMP280_ReadReg(BME280_REGISTER_DIG_H6);
  }
  BMP280DumpCalibration();
  HAL_Delay(50);

  //Настроим на ежесекундное обновление данных и фильтр пока на 4
  BMP280_WriteReg(BME280_REG_CONFIG, BME280_STBY_1000|BME280_FILTER_4);
  HAL_Delay(50);
  if(HAVE_BME_280 & BMP280Present)
  {
    // Влажность х2
    BMP280_WriteReg(BME280_REG_CTRL_HUM, BME280_OSRS_H_x2);
  }
  // Давление будем считывать 16 раз x16. Температуру 2 раза x2. Режим работы нормальный. Обновление по интервалу
  BMP280_WriteReg(BME280_REG_CTRL_MEAS, BME280_OSRS_T_x2|BME280_OSRS_P_x4|BME280_MODE_NORMAL);
  //  printf("T1 %u, T2 %d, T3, %d, P9 %d\n", calibData.dig_T1, calibData.dig_T2, calibData.dig_T3, calibData.dig_P9);
//  printf("sizeof(BMP280Data): %d", sizeof(BMP280Data));
}

//----------------------------------------------------------------------------------------------------------------------
void BMP280ReadData()
{
  if(!BMP280Present)
    return;
  int readSize = BMP280_DATA_SIZE;
  if(BMP280Present & HAVE_BME_280)
    readSize = BME280_DATA_SIZE;

  // Прочтём регистры за один проход
  HAL_I2C_Mem_Read(hi2cBMP, BMx280_Addr, BMP280_REG_PRESS_MSB, I2C_MEMADD_SIZE_8BIT, BMP280Data, readSize, TIME_OUT);

//  printf("P: %X %X %X | T: %X %X %X\n", BMP280Data[0], BMP280Data[1], BMP280Data[2], BMP280Data[3], BMP280Data[4], BMP280Data[5]);
  int32_t PressRAW = 0;
  PressRAW |= BMP280Data[0]<<12;
  PressRAW |= BMP280Data[1]<<4;
  PressRAW |= BMP280Data[2]>>4;

  int32_t TempRAW = 0;
  TempRAW |= BMP280Data[3]<<12;
  TempRAW |= BMP280Data[4]<<4;
  TempRAW |= BMP280Data[5]>>4;

  int32_t realT = bmp280_compensate_T_int32(TempRAW);
//  uint32_t realP = bmp280_compensate_P_int32(PressRAW);
  uint32_t realP = bmp280_compensate_P_int64(PressRAW)/256;
  uint32_t mmHgP = realP*3/4;
  // 101 325 / 760 ≈ 133,322 368 4 Па.
  // Норма атмосферного давления составляет 760 мм рт. ст., или 101 325 Па
  //litlle endian
  uint16_t HumRAW = 0;
  uint32_t relalHum = 0;
  if(HAVE_BME_280 & BMP280Present)
  {// Output value of “47445” represents 47445/1024 = 46.333 %RH
    HumRAW = BMP280Data[7]|(BMP280Data[6]<<8);
    relalHum = bme280_compensate_H_int32((int32_t)HumRAW);
//    printf("Hum RAW 0x%X (0x%X %X), calc: %lu\n", HumRAW, BMP280Data[6], BMP280Data[7], relalHum/1024);
  }
  relalHum *= 100;
  relalHum /= 1024;
//  printf("BMP280 T: %ld, P: %lu, mm.Hg: %lu, Hum: %lu%%\n", realT, realP, mmHgP, relalHum);
  BMP280Temperature = realT;  // Пересчитаная температура
  BMP280Pressure = mmHgP;     // Пересчитаное давление
  BMP280Humidity = relalHum;  // Пересчитаная влажность

}

//----------------------------------------------------------------------------------------------------------------------
void BMP280MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  printf("BMP280MasterRxCpltCallback\n");
}

//----------------------------------------------------------------------------------------------------------------------
uint8_t BMP280_ReadReg(uint16_t reg)
{
  uint8_t value;
  HAL_I2C_Mem_Read(hi2cBMP, BMx280_Addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, TIME_OUT);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
uint16_t BMP280_ReadReg_U16(uint16_t reg)
{
  uint16_t value= -1;
  HAL_I2C_Mem_Read(hi2cBMP, BMx280_Addr, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&value), 2, TIME_OUT);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
int16_t BMP280_ReadReg_I16(uint16_t reg)
{
  int16_t value = -1;
  HAL_I2C_Mem_Read(hi2cBMP, BMx280_Addr, reg, I2C_MEMADD_SIZE_8BIT, (uint8_t*)(&value), 2, TIME_OUT);
  return value;
}

//----------------------------------------------------------------------------------------------------------------------
void BMP280_WriteReg(uint8_t reg, uint8_t value)
{
  HAL_I2C_Mem_Write(hi2cBMP, BMx280_Addr, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, &value, 1, TIME_OUT);
}

//----------------------------------------------------------------------------------------------------------------------
void BMP280DumpCalibration()
{
  printf("----------------------------\n");
  printf("Calibration data\n");
  printf("dig_T1: %d\n", calibData.dig_T1);
  printf("dig_T2: %d\n", calibData.dig_T2);
  printf("dig_T3: %d\n", calibData.dig_T3);
  printf("dig_P1: %d\n", calibData.dig_P1);
  printf("dig_P2: %d\n", calibData.dig_P2);
  printf("dig_P3: %d\n", calibData.dig_P3);
  printf("dig_P4: %d\n", calibData.dig_P4);
  printf("dig_P5: %d\n", calibData.dig_P5);
  printf("dig_P6: %d\n", calibData.dig_P6);
  printf("dig_P7: %d\n", calibData.dig_P7);
  printf("dig_P8: %d\n", calibData.dig_P8);
  printf("dig_P9: %d\n", calibData.dig_P9);
  if(HAVE_BME_280 & BMP280Present)
  {
    printf("dig_H1: %d\n", calibDataHum.dig_H1);
    printf("dig_H2: %d\n", calibDataHum.dig_H2);
    printf("dig_H3: %d\n", calibDataHum.dig_H3);
    printf("dig_H4: %d\n", calibDataHum.dig_H4);
    printf("dig_H5: %d\n", calibDataHum.dig_H5);
    printf("dig_H6: %d\n", calibDataHum.dig_H6);

  }
  printf("----------------------------\n");
}

//----------------------------------------------------------------------------------------------------------------------
// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
// t_fine carries fine temperature as global value
int32_t t_fine;
int32_t bmp280_compensate_T_int32(int32_t adc_T)
{
  int32_t var1;
  int32_t var2;
  int32_t T;
  var1  = ((((adc_T>>3) - ((int32_t)calibData.dig_T1<<1))) * ((int32_t)calibData.dig_T2)) >> 11;
  var2  = (((((adc_T>>4) - ((int32_t)calibData.dig_T1)) * ((adc_T>>4) - ((int32_t)calibData.dig_T1))) >> 12) *
             ((int32_t)calibData.dig_T3)) >> 14;
  t_fine = var1 + var2;
  T  = (t_fine * 5 + 128) >> 8;
  return T;
}


//----------------------------------------------------------------------------------------------------------------------
// Returns pressure in Pa as unsigned 32 bit integer. Output value of “96386” equals 96386 Pa = 963.86 hPa
uint32_t bmp280_compensate_P_int32(int32_t adc_P)
{
  int32_t var1;
  int32_t var2;
  uint32_t p;
  var1 = (((uint32_t)t_fine)>>1) - (int32_t)64000;
  var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((uint32_t)calibData.dig_P6);
  var2 = var2 + ((var1*((int32_t)calibData.dig_P5))<<1);
  var2 = (var2>>2)+(((int32_t)calibData.dig_P4)<<16);
  var1 = (((calibData.dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((uint32_t)calibData.dig_P2) * var1)>>1))>>18;
  var1 =((((32768+var1))*((int32_t)calibData.dig_P1))>>15);
  if(var1 == 0)
  {
    return 0; // avoid exception caused by division by zero
  }
  p = (((uint32_t)(((int32_t)1048576)-adc_P)-(var2>>12)))*3125;
  if(p < 0x80000000)
  {
    p = (p << 1) / ((uint32_t)var1);
  }
  else
  {
    p = (p / (uint32_t)var1) * 2;
  }
  var1 = (((int32_t)calibData.dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
  var2 = (((int32_t)(p>>2)) * ((int32_t)calibData.dig_P8))>>13;
  p = (uint32_t)((int32_t)p + ((var1 + var2 + calibData.dig_P7) >> 4));
  return p;
}

//----------------------------------------------------------------------------------------------------------------------
// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
uint32_t bmp280_compensate_P_int64(int32_t adc_P)
{
  int64_t var1;
  int64_t var2;
  int64_t p;
  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)calibData.dig_P6;
  var2 = var2 + ((var1*(int64_t)calibData.dig_P5)<<17);
  var2 = var2 + (((int64_t)calibData.dig_P4)<<35);
  var1 = ((var1 * var1 * (int64_t)calibData.dig_P3)>>8) + ((var1 * (int64_t)calibData.dig_P2)<<12);
  var1 = (((((int64_t)1)<<47)+var1))*((int64_t)calibData.dig_P1)>>33;
  if   (var1 == 0)
  {
    return 0; // avoid exception caused by division by zero
  }
  p = 1048576-adc_P;
  p = (((p<<31)-var2)*3125)/var1;
  var1 = (((int64_t)calibData.dig_P9) * (p>>13) * (p>>13)) >> 25;
  var2 = (((int64_t)calibData.dig_P8) * p) >> 19;
  p = ((p + var1 + var2) >> 8) + (((int64_t)calibData.dig_P7)<<4);
  return (uint32_t)p;

}

//----------------------------------------------------------------------------------------------------------------------
// Returns humidity in %RH as unsigned 32 bit integer in Q22.10 format (22 integer and 10 fractional bits).
// Output value of “47445” represents 47445/1024 = 46.333 %RH
uint32_t bme280_compensate_H_int32(int32_t adc_H)
{
  int32_t v_x1_u32r;
  v_x1_u32r = (t_fine - ((int32_t)76800));
  v_x1_u32r = (((((adc_H << 14) - (((int32_t)calibDataHum.dig_H4) << 20) - (((int32_t)calibDataHum.dig_H5) * v_x1_u32r)) +
             ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)calibDataHum.dig_H6)) >> 10) *
             (((v_x1_u32r * ((int32_t)calibDataHum.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
             ((int32_t)2097152)) * ((int32_t)calibDataHum.dig_H2) + 8192) >> 14));
  v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)calibDataHum.dig_H1)) >> 4));
  v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
  v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
  return (uint32_t)(v_x1_u32r>>12);
}
