/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void ReceiveUSB(uint8_t *str, uint32_t len);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BTN_RESET_Pin GPIO_PIN_0
#define BTN_RESET_GPIO_Port GPIOA
#define BTN_RESET_EXTI_IRQn EXTI0_IRQn
#define BTN_SET_Pin GPIO_PIN_1
#define BTN_SET_GPIO_Port GPIOA
#define BTN_SET_EXTI_IRQn EXTI1_IRQn
#define BTN_MID_Pin GPIO_PIN_2
#define BTN_MID_GPIO_Port GPIOA
#define BTN_MID_EXTI_IRQn EXTI2_IRQn
#define BTN_RIGHT_Pin GPIO_PIN_3
#define BTN_RIGHT_GPIO_Port GPIOA
#define BTN_RIGHT_EXTI_IRQn EXTI3_IRQn
#define BTN_LEFT_Pin GPIO_PIN_4
#define BTN_LEFT_GPIO_Port GPIOA
#define BTN_LEFT_EXTI_IRQn EXTI4_IRQn
#define BTN_DOWN_Pin GPIO_PIN_5
#define BTN_DOWN_GPIO_Port GPIOA
#define BTN_DOWN_EXTI_IRQn EXTI9_5_IRQn
#define BTN_UP_Pin GPIO_PIN_6
#define BTN_UP_GPIO_Port GPIOA
#define BTN_UP_EXTI_IRQn EXTI9_5_IRQn
#define LED_Pin GPIO_PIN_11
#define LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
