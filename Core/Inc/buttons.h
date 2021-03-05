/*
 * buttons.h
 *
 *  Created on: Jan 28, 2021
 *      Author: lex
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <buttons.h>

typedef enum ButtonClick_t
{
  buttonNoClick,
  buttonClick,
  buttonLongClick
}ButtonClick;

extern volatile uint16_t GPIO_Press_Pin;
extern volatile ButtonClick haveClick;

void clickButton();
void longClickButton();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void enableInterupt();
void disableInterupt();

void clearFlag();

void longClickButtonCallback();

#endif /* INC_BUTTONS_H_ */
