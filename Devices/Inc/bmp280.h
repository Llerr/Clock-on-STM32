/*
 * bmp280.h
 *
 *  Created on: 3 февр. 2021 г.
 *      Author: lex
 */

#ifndef INC_BMP280_H_
#define INC_BMP280_H_

#include "i2c.h"


#ifdef __cplusplus
extern "C" {
#endif

//Адрес устройства на шине i2c
#define BMP280_ADDRESS (0x76<<1) /// BMP280 I2C ADDRES

extern int BMP280Temperature; ///< Пересчитаная температура
extern int BMP280Pressure; ///< Пересчитаное давление

/**
 * Начальная инициализация и проверка наличия
 */
void BMP280Init(I2C_HandleTypeDef *hi2c);

/**
 * Прочитать значение температуры и давления, пересчитать в реальные и сохранить в переменных
 */
void BMP280ReadData();

void BMP280MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);
void BMP280MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);
/**
 * Чтение из регистраs
 */
uint8_t BMP280_ReadReg(uint16_t reg);
uint16_t BMP280_ReadReg_U16(uint16_t reg);
int16_t  BMP280_ReadReg_I16(uint16_t reg);
/**
 * Запись в регистр
 */
void BMP280_WriteReg(uint8_t reg, uint8_t value);

void BMP280DumpCalibration();

/// Returns temperature in DegC, resolution is 0.01 DegC. Output value of “5123” equals 51.23 DegC.
int32_t bmp280_compensate_T_int32(int32_t adc_T);

/// Returns pressure in Pa as unsigned 32 bit integer. Output value of “96386” equals 96386 Pa = 963.86 hPa
uint32_t bmp280_compensate_P_int32(int32_t adc_P);



#ifdef __cplusplus
}
#endif

#endif /* INC_BMP280_H_ */
