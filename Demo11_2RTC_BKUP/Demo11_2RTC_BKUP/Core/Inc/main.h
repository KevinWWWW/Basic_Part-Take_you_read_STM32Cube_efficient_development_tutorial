/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KeyLeft_Pin GPIO_PIN_2
#define KeyLeft_GPIO_Port GPIOE
#define KeyDown_Pin GPIO_PIN_3
#define KeyDown_GPIO_Port GPIOE
#define KeyRight_Pin GPIO_PIN_4
#define KeyRight_GPIO_Port GPIOE
#define LED1_Pin GPIO_PIN_9
#define LED1_GPIO_Port GPIOF
#define LED2_Pin GPIO_PIN_10
#define LED2_GPIO_Port GPIOF
#define KeyUp_Pin GPIO_PIN_0
#define KeyUp_GPIO_Port GPIOA
#define LCD_BL_Pin GPIO_PIN_15
#define LCD_BL_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
void RTC_ToggleReset();
void RTC_SaveToBKUP();
void RTC_LoadFromBKUP();
void RTC_ReadBKUP();
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
