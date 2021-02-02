/*
 * AHT10.c
 *
 *  Created on: Jan 31, 2021
 *      Author: lex
 */

#include <stdio.h>

#include "i2c.h"

/* Variables for AHT10 */
uint8_t AHT10_RX_Data[6];
uint AHT10_Temperature;
uint AHT10_Humidity;

//uint8_t AHT10_TmpHum_Cmd[3] = {0xAC, 0x33, 0x00};
uint8_t AHT10_TmpHum_Cmd = 0xAC;
uint8_t AHT10_Init_Cmd = 0xE1;
uint8_t AHT10_Reset_Cmd = 0xBA;


#include "aht10.h"

//----------------------------------------------------------------------------------------------------------------------
void AHT10Init(I2C_HandleTypeDef *hi2c)
{
  printf("Start AHT10\n");
  HAL_I2C_Master_Transmit(hi2c, AHT10_ADRESS, &AHT10_Init_Cmd, 1, 100);
  HAL_I2C_Master_Transmit(hi2c, AHT10_ADRESS, &AHT10_Reset_Cmd, 1, 100);
  printf("AHT10 started\n");
//  HAL_I2C_Master_Transmit_IT (&hi2c1, AHT10_Adress, uint8_t *pData, uint16_t Size);
}

//----------------------------------------------------------------------------------------------------------------------
void AHT10RequestData(I2C_HandleTypeDef *hi2c)
{
  HAL_I2C_Master_Transmit(hi2c, AHT10_ADRESS, &AHT10_Reset_Cmd, 1, 100);
 printf("Request data from AHT10\n");
  HAL_I2C_Master_Transmit_IT(hi2c, AHT10_ADRESS, &AHT10_TmpHum_Cmd, 1);
}

//----------------------------------------------------------------------------------------------------------------------
void AHT10MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  printf("AHT10_MasterTxCpltCallback: XferCount=%d\n", hi2c->XferCount);
//  if(hi2c->XferCount > 1)
  {
    printf("---> Send command for get data\n");
    HAL_I2C_Master_Receive_IT(hi2c, AHT10_ADRESS, (uint8_t*)AHT10_RX_Data, 6);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void AHT10MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
  uint32_t AHT10_ADC_Raw;

  printf("AHT10MasterRxCpltCallback: state(0x%X): %02X %02X %02X %02X %02X)\n",AHT10_RX_Data[0],
      AHT10_RX_Data[1], AHT10_RX_Data[2], AHT10_RX_Data[3], AHT10_RX_Data[4], AHT10_RX_Data[5]);
//  if(~AHT10_RX_Data[0] & 0x80)
  {
    /* Convert to Temperature in °C */
    AHT10_ADC_Raw = (((uint32_t)AHT10_RX_Data[3] & 15) << 16) | ((uint32_t)AHT10_RX_Data[4] << 8) | AHT10_RX_Data[5];
    AHT10_Temperature = (AHT10_ADC_Raw * 200 / 1048576) - 50;
    printf("Temperature raw: %lu\n", AHT10_ADC_Raw);
    /* Convert to Relative Humidity in % */
    AHT10_ADC_Raw = ((uint32_t)AHT10_RX_Data[1] << 12) | ((uint32_t)AHT10_RX_Data[2] << 4) | (AHT10_RX_Data[3] >> 4);
    AHT10_Humidity = (float)(AHT10_ADC_Raw*100/1048576);
    printf("Humidity raw: %lu\n", AHT10_ADC_Raw);
    printf("Temperature %u, Humidity %u\n", AHT10_Temperature, AHT10_Humidity);
  }
//  else
//  {
//    puts("~AHT10_RX_Data[0] & 0x80");
//  }
}
