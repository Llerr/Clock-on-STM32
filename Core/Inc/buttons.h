/*
 * buttons.h
 *
 *  Created on: Jan 28, 2021
 *      Author: lex
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <buttons.h>

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void enableInterupt();
void disableInterupt();

void clearFlag();

void clickButton();
void longClickButton();

#endif /* INC_BUTTONS_H_ */
