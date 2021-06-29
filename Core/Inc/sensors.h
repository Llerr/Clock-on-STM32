/*
 * sensors.h
 *
 *  Created on: Jan 31, 2021
 *      Author: lex
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

//#include "aht10.h"

extern int temperature;
extern int humidity;
extern int pressure;
extern int illumination;

#ifdef __cplusplus
extern "C" {
#endif

void initSensors();

void requestDataSensors();

#ifdef __cplusplus
}
#endif

#endif /* INC_SENSORS_H_ */
