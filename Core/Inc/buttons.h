/*
 * buttons.h
 *
 *  Created on: Jan 28, 2021
 *      Author: lex
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_

#include <stdint.h>

#include "buttons.h"

typedef enum ButtonClick_t
{
  buttonNoClick,
  buttonClick,
  buttonLongClick
}ButtonClick;

extern volatile uint16_t GPIO_Press_Pin;
extern volatile ButtonClick haveClick;
extern int8_t editNum;

//void (*buttonReceiver)(); ///< Получатель событий кнопок

void buttonReceiverMenu();
void buttonReceiverTimeEdit();
void buttonReceiverAlarmEdit();
void buttonReceiverDateEdit();
void buttonReceiverCountdownEdit();
void buttonReceiverBrightEdit();

void clickButton();
void longClickButton();
void clickMidButton();

void initButtons();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void enableInterupt();
void disableInterupt();

void clearFlag();

void longClickButtonCallback();

#endif /* INC_BUTTONS_H_ */
