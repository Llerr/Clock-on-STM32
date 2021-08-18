/*
 * AHT10.c
 *
 *  Created on: Jan 31, 2021
 *      Author: lex
 */

#include <stdio.h>
#include "i2c.h"

#define USE_INTERRUPT

/// Указатель на канал I2C
I2C_HandleTypeDef *hi2cAHT10 = NULL;

/* Variables for AHT10 */
uint8_t AHT10_RX_Data[6];
int AHT10Temperature = 30000;
uint32_t AHT10Humidity = 0;

uint8_t AHT10_TmpHum_Cmd[3] = {0xAC, 0x33, 0x00};
//uint8_t AHT10_TmpHum_Cmd = 0xAC;
uint8_t AHT10_Init_Cmd = 0xE1;
uint8_t AHT10_Reset_Cmd = 0xBA;

char AHT10Present = 0;

#include "aht10.h"

//----------------------------------------------------------------------------------------------------------------------
void AHT10Init(I2C_HandleTypeDef *hi2c)
{
  printf("Start init AHT10\n");
  if(HAL_I2C_Master_Transmit(hi2c, AHT10_ADRESS, &AHT10_Init_Cmd, 1, 1000)!= HAL_OK)
  {
    printf("- AHT10 not found!\n");
    AHT10Present = 0;
    return;
  }
  hi2cAHT10 = hi2c;
  AHT10Present = 1;
//  HAL_I2C_Master_Transmit(hi2c, AHT10_ADRESS, &AHT10_Reset_Cmd, 1, 1000);
  printf("+ AHT10 started!\n");
  HAL_Delay(50);
//  HAL_I2C_Master_Transmit_IT (&hi2c1, AHT10_Adress, uint8_t *pData, uint16_t Size);
  AHT10Reset();
  HAL_Delay(30);
}

//----------------------------------------------------------------------------------------------------------------------
void AHT10Reset()
{
  HAL_I2C_Master_Transmit(hi2cAHT10, AHT10_ADRESS, &AHT10_Reset_Cmd, 1, 1000);
}
//----------------------------------------------------------------------------------------------------------------------
void AHT10RequestData()
{
  if(!AHT10Present) return;
  // Запросим данные
#ifdef USE_INTERRUPT
//  HAL_I2C_Master_Transmit_IT(hi2cAHT10, AHT10_ADRESS, &AHT10_TmpHum_Cmd, 1);
  HAL_I2C_Master_Transmit_IT(hi2cAHT10, AHT10_ADRESS, AHT10_TmpHum_Cmd, 3);
#else
  static uint8_t send = 1;
  if(send)
    HAL_I2C_Master_Transmit(hi2cAHT10, AHT10_ADRESS, AHT10_TmpHum_Cmd, 3, 1000);
  else
  {
    HAL_I2C_Master_Receive(hi2cAHT10, AHT10_ADRESS, (uint8_t*)AHT10_RX_Data, 6, 1000);
    AHT10MasterRxCpltCallback(NULL); // Пересчитаем значения
  }
  send = !send;
#endif //USE_INTERRUPT
}

//----------------------------------------------------------------------------------------------------------------------
void AHT10MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
//  if(hi2c->XferCount > 1)
  {
    HAL_I2C_Master_Receive_IT(hi2c, AHT10_ADRESS, (uint8_t*)AHT10_RX_Data, 6);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void AHT10MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  uint32_t AHT10_ADC_Raw;

  /* Convert to Temperature in °C */
  AHT10_ADC_Raw = (((uint32_t)AHT10_RX_Data[3] & 15) << 16) | ((uint32_t)AHT10_RX_Data[4] << 8) | AHT10_RX_Data[5];
  AHT10Temperature = ((AHT10_ADC_Raw/1024) * 200*100 )/ 1024 - 50*100;
  //    printf("Temperature raw: %lu\n", AHT10_ADC_Raw);
  /* Convert to Relative Humidity in % */
  AHT10_ADC_Raw = ((uint32_t)AHT10_RX_Data[1] << 12) | ((uint32_t)AHT10_RX_Data[2] << 4) | (AHT10_RX_Data[3] >> 4);
  AHT10Humidity = ((AHT10_ADC_Raw/1024)*10000/1024);
  //    printf("Humidity raw: %lu\n", AHT10_ADC_Raw);
//  printf("AHT10 t: %u, H: %lu\n", AHT10_Temperature, AHT10_Humidity);
}
