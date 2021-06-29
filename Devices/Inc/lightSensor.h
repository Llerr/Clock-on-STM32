/*
 * lightSensor.h
 *
 *  Created on: May 3, 2021
 *      Author: lex
 *
 *      MAX44009 ligth sensor
 */

#ifndef INC_LIGHTSENSOR_H_
#define INC_LIGHTSENSOR_H_

#define MAX44009_WRITE_ADDR 0b10010101
#define MAX44009_READ_ADDR  0b10010100

extern int brightness;

void MAX44009Init(I2C_HandleTypeDef *hi2c);

/**
 * Запросить данные у датчика AHT10
 * @param hi2c указатель на обмен i2c
 */
void MAX44009RequestData();

void MAX44009_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c);

#endif /* INC_LIGHTSENSOR_H_ */
