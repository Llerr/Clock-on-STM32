/*
 * AHT10.h
 *
 *  Created on: Jan 31, 2021
 *      Author: lex
 */

#ifndef INC_AHT10_H_
#define INC_AHT10_H_

#define AHT10_ADRESS (0x38 << 1)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Инициализировать датчик AHT10
 * @param hi2c указатель на обмен i2c
 */
void AHT10Init(I2C_HandleTypeDef *hi2c);

/**
 * Запросить данные у датчика AHT10
 * @param hi2c указатель на обмен i2c
 */
void AHT10RequestData(I2C_HandleTypeDef *hi2c);

void AHT10MasterTxCpltCallback(I2C_HandleTypeDef *hi2c);

void AHT10MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);

#ifdef __cplusplus
}
#endif
#endif /* INC_AHT10_H_ */
