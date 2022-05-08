/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
// FLASH 512 Kb RAM 64Kb
//volatile
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>

#include "buttons.h"
#include "sensors.h"
#include "backup.h"

#include "aht10.h"
#include "MatrixRGB.h"
#include "Screen/Screens.h"
#include "pomidoro.h"

#include "audio.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern void initialise_monitor_handles(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// printf() через SWD
//int __io_putchar(int ch)
//{
//  ITM_SendChar(ch);
//  return ch;
//}
int __io_putchar(int ch)
{
  ITM_SendChar((uint32_t)ch);
  return ch;
}

// Вывод printf через VCP.
//int _write_r (struct _reent *r, int file, char * ptr, int len)
//{
//  (void)r;
//  (void)file;
//  CDC_Transmit_FS((uint8_t *)ptr, len);
//  return len;
//}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_RTC_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_DAC_Init();
  MX_TIM1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
//  sTime.Hours = 16;
//  sTime.Minutes = 32;
//  sTime.Seconds = 51;
//  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//  sDate.Date = 20;
//  sDate.Month = 1;
//  sDate.Year = 21;
//  HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

  puts(" "); // Для вывода первого символа, чтобы не съедало
  printf("Button data size: %ld\n", buttonSound.dataLength);
  HAL_Delay(100);
  initButtons();
  initSensors();
  initScreens();
  initMatrix();
  initAudio();
  //для i2c
  HAL_I2C_EV_IRQHandler(&hi2c1);

  //HAL_RTC_GetAlarm();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  char str_tx[30];
//  char str_rx[255];
//  uint32_t len=0;
//  HAL_Delay(500);
//  sprintf(str_tx,"USB send data\n");

  // Для секундного таймера
  HAL_RTCEx_SetSecond_IT(&hrtc);
  //Таймер для экрана
  HAL_TIM_Base_Start_IT(&htim2);
  drawScreen(screenCur);
  HAL_TIM_Base_Start_IT(&htim4); // Таймер для миганий
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
//  HAL_DAC_Start(hdac, Channel);
//  saveDateBKP(&sDateEdit);
  loadDateBKP(&sDate);
  loadAlarmsBKP();
  loadBrightnessBKP();
  loadPomidoroBKP();
  setDate(&sDate);
  getTime(&sTime);

  resetPomidoro();

  puts("Enter to loop");
  while (1)
  {
    switch(haveClick)
    {
    case buttonClick:
      clickButton();
      break;
    case buttonLongClick:
      longClickButton();
      break;
    default:
      break;
    }
  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//  HAL_RTCEx_SetSmoothCalib(hrtc, SmoothCalibPeriod, SmoothCalibPlusPulses, SmouthCalibMinusPulsesValue);
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void ReceiveUSB(uint8_t *str, uint32_t len)
{
  str[len] = 0;
  printf("Receeive string[%s], len: %lu\n", str, len);
}

//----------------------------------------------------------------------------------------------------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM2) //check if the interrupt comes from TIM2
  {
    updateScreen();
  }
  else if(htim->Instance == TIM3)
  {
//      printf("HAL_TIM_PeriodElapsedCallback\n");
    longClickButtonCallback();
  }
  else if(htim->Instance == TIM4)
  {
    blink(1); // Тут меняем цвет
  }
}

//----------------------------------------------------------------------------------------------------------------------
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
//  printf("HAL_TIM_OC_DelayElapsedCallback\n");
  enableInterupt();
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  printf("Error_Handler\n");
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
