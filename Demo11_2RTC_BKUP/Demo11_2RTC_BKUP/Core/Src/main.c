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
int main(void) {
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
	__HAL_RTC_WAKEUPTIMER_DISABLE(&hrtc);
	lcd_init();
	lcd_show_str(0, 10, 16, "Demo11_2:Using Backup Registers", RED);
	uint32_t iniRTC = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0);
	if ((iniRTC & 0x01) == 0) {
		lcd_show_str(0, 30, 16, "Reset RTC time on startup: Yes", RED);
	} else {
		lcd_show_str(0, 30, 16, "Reset RTC time on startup: No ", RED);
	}
	lcd_show_str(0, 70, 16, "[1]KeyUp    = Reset RTC time on startup", RED);
	lcd_show_str(0, 90, 16, "[2]KeyLeft  = Save current time to BKUP", RED);
	lcd_show_str(0, 110, 16, "[3]KeyRight = Change RTC time from BKUP", RED);
	lcd_show_str(0, 130, 16, "[4]KeyDown  = Read BKUP registers      ", RED);
	__HAL_RTC_WAKEUPTIMER_ENABLE(&hrtc);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		KEYS curKey = ScanPressedKey(KEY_WAIT_ALWAYS);
		lcd_fill(0, 170, 320, 270, WHITE);
		switch (curKey) {
		case KEY_UP:
			RTC_ToggleReset();
			break;
		case KEY_LEFT:
			RTC_SaveToBKUP();
			break;
		case KEY_RIGHT:
			RTC_LoadFromBKUP();
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
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE
			| RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
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
		sprintf(str, "Current Time = %2d:%2d:%2d", sTime.Hours,
				sTime.Minutes, sTime.Seconds);
		lcd_show_str(0, 50, 16, str, RED);
	}
}

void RTC_ToggleReset() {
	uint32_t iniRTC = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0);
	iniRTC = !iniRTC;
	if ((iniRTC & 0x01) == 0) {
		lcd_show_str(0, 170, 16, "Reset RTC time on startup    ", RED);
	} else {
		lcd_show_str(0, 170, 16, "Not reset RTC time on startup", RED);
	}
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR0, iniRTC);
}

void RTC_SaveToBKUP() {
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK) {
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x01);
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR2, sTime.Hours);
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR3, sTime.Minutes);
		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR4, sTime.Seconds);

		char str[40];
		/* Show Time */
		sprintf(str, "Current Time = %2d:%2d:%2d", sTime.Hours,
				sTime.Minutes, sTime.Seconds);
		lcd_show_str(0, 170, 16, str, RED);
		lcd_show_str(0, 190, 16, "Current Time is saved in BKUP", RED);
	}
}

void RTC_LoadFromBKUP() {
	if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1)) {
		RTC_TimeTypeDef sTime;
		sTime.Hours   = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
		sTime.Minutes = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
		sTime.Seconds = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
		HAL_Delay(10);
		if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK) {
			lcd_show_str(0, 170, 16, "Load BKUP time, success", RED);
		} else {
			lcd_show_str(0, 170, 16, "Load BKUP time, error", RED);
		}
	} else {
		lcd_show_str(0, 170, 16, "No BKUP time is saved", RED);
	}
}

void RTC_ReadBKUP() {
	uint32_t regValue;
	char str[40];

	regValue = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0);
	sprintf(str, "Reset RTC, BKP_DR0 = %lu", regValue);
	lcd_show_str(0, 170, 16, str, RED);

	regValue = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
	sprintf(str, "Time is saved, BKP_DR1 = %lu", regValue);
	lcd_show_str(0, 190, 16, str, RED);

	regValue = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2);
	sprintf(str, "Saved time (Hour), BKP_DR2 = %lu", regValue);
	lcd_show_str(0, 210, 16, str, RED);

	regValue = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3);
	sprintf(str, "Saved time (Min), BKP_DR3 = %lu", regValue);
	lcd_show_str(0, 230, 16, str, RED);

	regValue = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4);
	sprintf(str, "Saved time (Sec), BKP_DR4 = %lu", regValue);
	lcd_show_str(0, 250, 16, str, RED);
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
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
