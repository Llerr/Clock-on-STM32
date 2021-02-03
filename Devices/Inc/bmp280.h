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

/**
 * Начальная инициализация и проверка наличия
 */
void BMP280Init(I2C_HandleTypeDef *hi2c);
/**
 * Чтение из регистраs
 */
uint8_t BMP280_ReadReg(uint8_t reg);
/**
 * Запись в регистр
 */
BMP280_WriteReg(uint8_t reg, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* INC_BMP280_H_ */
