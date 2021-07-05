/*
 * pictures.h
 *
 *  Created on: Jul 1, 2021
 *      Author: lex
 */

#ifndef INC_PICTURES_H_
#define INC_PICTURES_H_

typedef struct Picture_t
{
  uint16_t width;
  uint16_t heght;
  const uint8_t *data;
} Picture;

//----------------------------------------------------------------------------------------------------------------------
extern Picture picCalendar;
extern Picture picHumidity;
extern Picture picPressure;
extern Picture picTemperature;

extern Picture picIllumination;
extern Picture picBrightness;

extern Picture picNum1;
extern Picture picNum2;
extern Picture picNum3;
extern Picture picBell;

#endif /* INC_PICTURES_H_ */
