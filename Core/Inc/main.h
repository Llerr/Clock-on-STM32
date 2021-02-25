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
#define MATRX_R1_Pin GPIO_PIN_0
#define MATRX_R1_GPIO_Port GPIOC
#define MATRX_G1_Pin GPIO_PIN_1
#define MATRX_G1_GPIO_Port GPIOC
#define MATRX_B1_Pin GPIO_PIN_2
#define MATRX_B1_GPIO_Port GPIOC
#define MATRX_R2_Pin GPIO_PIN_3
#define MATRX_R2_GPIO_Port GPIOC
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
#define MATRX_G2_Pin GPIO_PIN_4
#define MATRX_G2_GPIO_Port GPIOC
#define MATRX_B2_Pin GPIO_PIN_5
#define MATRX_B2_GPIO_Port GPIOC
#define MATRX_A_Pin GPIO_PIN_6
#define MATRX_A_GPIO_Port GPIOC
#define MATRX_B_Pin GPIO_PIN_7
#define MATRX_B_GPIO_Port GPIOC
#define MATRX_C_Pin GPIO_PIN_8
#define MATRX_C_GPIO_Port GPIOC
#define MATRX_D_Pin GPIO_PIN_9
#define MATRX_D_GPIO_Port GPIOC
#define MATRX_CLK_Pin GPIO_PIN_10
#define MATRX_CLK_GPIO_Port GPIOC
#define MATRX_STB_Pin GPIO_PIN_11
#define MATRX_STB_GPIO_Port GPIOC
#define MATRX_OE_Pin GPIO_PIN_12
#define MATRX_OE_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */
#define BTN_GPIO_Port BTN_DOWN_GPIO_Port
#define MATRX_GPIO_Port GPIOC
#define  MATRX_RGB1_Pins (MATRX_R1_Pin|MATRX_G1_Pin|MATRX_B1_Pin)
#define  MATRX_RGB2_Pins (MATRX_R2_Pin|MATRX_G2_Pin|MATRX_B2_Pin)
#define  MATRX_RGB_Pins  (MATRX_RGB1_Pins|MATRX_RGB2_Pins)
#define  MATRX_ADDR_Pins (MATRX_A_Pin|MATRX_B_Pin|MATRX_C_Pin|MATRX_D_Pin)
#define  MATRX_ALL_Pins  (MATRX_RGB_Pins|MATRX_ADDR_Pins|MATRX_CLK_Pin|MATRX_STB_Pin|MATRX_OE_Pin)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
