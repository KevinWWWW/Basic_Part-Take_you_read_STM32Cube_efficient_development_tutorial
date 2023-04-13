/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lcd.h"
#include "keyled.h"
#include <stdio.h>
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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_FSMC_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	lcd_init();
	__HAL_RTC_WAKEUPTIMER_DISABLE(&hrtc);
	lcd_show_str(0, 0, 16, "Demo11_3:RTC Tamper and TtimeStamp ", RED);
	lcd_show_str(0, 20, 16, "Please connect PE2 and PC13 by line", RED);
	lcd_show_str(0, 40, 16, "KeyRight simulate tamper event     ", RED);

	lcd_show_str(0, 100, 16, "[1]KeyUp    = Save time to BKUP    ", RED);
	lcd_show_str(0, 120, 16, "[2]KeyDown  = Read BKUP registers  ", RED);
	lcd_show_str(0, 140, 16, "[3]KeyRight = Trigger tamper event ", RED);
	__HAL_RTC_WAKEUPTIMER_ENABLE(&hrtc);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
		KEYS curKey = ScanPressedKey(KEY_WAIT_ALWAYS);
		lcd_fill(0, 170, 320, 270, WHITE);
		switch (curKey) {
		case KEY_UP:
			RTC_SaveToBKUP();
			break;
		case KEY_DOWN:
			RTC_ReadBKUP();
			break;
		default:
			break;
		}
		HAL_Delay(200);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 60;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	LED1_Toggle();
	if (HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK) {
		HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);
		char str[40];
		/* Show Time */
		sprintf(str, "%2d:%2d:%2d", sTime.Hours, sTime.Minutes,
				sTime.Seconds);
		lcd_show_str(0, 60, 16, str, RED);
	}
}

void HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc) {
	lcd_fill(0, 170, 320, 270, WHITE);
	lcd_show_str(0, 180, 16, "Tamper1 is triggered", RED);
	lcd_show_str(0, 200, 16, "All BKUP-Regs are cleared", RED);
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	if (HAL_RTCEx_GetTimeStamp(hrtc, &sTime, &sDate, RTC_FORMAT_BIN)
			== HAL_OK) {
		char str[40];
		/* Show Time */
		sprintf(str, "%2d:%2d:%2d", sTime.Hours, sTime.Minutes,
				sTime.Seconds);
		lcd_show_str(0, 220, 16, str, RED);
	}
}

void RTC_SaveToBKUP() {
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK) {
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, sTime.Hours);
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, sTime.Minutes);
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, sTime.Seconds);
		lcd_show_str(0, 180, 16, "Time is saved in BKUP", RED);
		char str[40];
		/* Show Time */
		sprintf(str, "%2d:%2d:%2d", sTime.Hours, sTime.Minutes,
				sTime.Seconds);
		lcd_show_str(0, 200, 16, str, RED);
	}
}

void RTC_ReadBKUP() {
	char str[40];
	sprintf(str, "saved time(Hour), BKP_DR2 = %lu",
			HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2));
	lcd_show_str(0, 180, 16, str, RED);

	sprintf(str, "saved time(Min),  BKP_DR3 = %lu",
			HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3));
	lcd_show_str(0, 200, 16, str, RED);

	sprintf(str, "saved time(Sec),  BKP_DR4 = %lu",
			HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4));
	lcd_show_str(0, 220, 16, str, RED);

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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
