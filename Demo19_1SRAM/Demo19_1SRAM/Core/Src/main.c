/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "rng.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "lcd.h"
#include "keyled.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SRAM_ADDR_BEGIN	0x68000000UL
#define SRAM_ADDR_HALF	0x68080000UL
#define SRAM_ADDR_END	0x680FFFFFUL
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
  MX_RNG_Init();
  /* USER CODE BEGIN 2 */
  lcd_init();
  lcd_show_str(10, 0 * 30 + 10, 24, "Demo19_1: External SRAM", RED);
  lcd_show_str(10, 1 * 30 + 10, 24, "Read/Write SRAM by polling", RED);

  lcd_show_str(10, 3 * 30 + 10, 24, "[1]KeyUp    = Write by HAL functions", RED);
  lcd_show_str(10, 4 * 30 + 10, 24, "[2]KeyDown  = Read by HAL functions", RED);
  lcd_show_str(10, 5 * 30 + 10, 24, "[3]KeyLeft  = Write by pointer", RED);
  lcd_show_str(10, 6 * 30 + 10, 24, "[4]KeyRight = Read by pointer", RED);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  KEYS curkey = ScanPressedKey(KEY_WAIT_ALWAYS);
	  switch (curkey) {
	  case KEY_UP:
		  lcd_fill(10, 7 * 30 + 10, 479, 14 * 30 + 10, WHITE);
		  SRAM_WriteByFunc();
		  break;
	  case KEY_DOWN:
		  lcd_fill(10, 7 * 30 + 10, 479, 14 * 30 + 10, WHITE);
		  SRAM_ReadByFunc();
		  break;
	  case KEY_LEFT:
		  lcd_fill(10, 7 * 30 + 10, 479, 14 * 30 + 10, WHITE);
		  SRAM_WriteByPointer();
		  break;
	  case KEY_RIGHT:
		  lcd_fill(10, 7 * 30 + 10, 479, 14 * 30 + 10, WHITE);
		  SRAM_ReadByPointer();
		  break;
	  }
	  lcd_show_str(10, 13 * 30 + 10, 24, "** Reselect menu or reset **", RED);
	  HAL_Delay(500);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void SRAM_WriteByFunc() {
	uint32_t *pAddr = (uint32_t *)(SRAM_ADDR_BEGIN);
	uint8_t strIn[] = "Moment in UPC";
	if (HAL_SRAM_Write_8b(&hsram3, pAddr, strIn, sizeof(strIn)) == HAL_OK) {
		lcd_show_str(10, 8 * 30 + 10, 24, "Write string at 0x6800 0000", RED);
		lcd_show_str(10, 9 * 30 + 10, 24, strIn, RED);
	}

	uint32_t random32bit;
	pAddr = (uint32_t *)(SRAM_ADDR_BEGIN + 0x100);
	HAL_RNG_GenerateRandomNumber(&hrng, &random32bit);
	if (HAL_SRAM_Write_32b(&hsram3, pAddr, &random32bit, 1) == HAL_OK) {
		lcd_show_str(10, 10 * 30 + 10, 24, "Write 32b random num at 0x6800 0100", RED);
		uint8_t tempStr[30];
		sprintf(tempStr, "0x%08X", random32bit);
		lcd_show_str(10, 11 * 30 + 10, 24, tempStr, RED);

	}
}

void SRAM_ReadByFunc() {
	uint32_t *pAddr = (uint32_t *)(SRAM_ADDR_BEGIN);
	uint8_t strOut[30];
	uint16_t dataLen = 30;
	if (HAL_SRAM_Read_8b(&hsram3, pAddr, &strOut, dataLen) == HAL_OK) {
		lcd_show_str(10, 8 * 30 + 10, 24, "Read string at 0x6800 0000 ", RED);
		lcd_show_str(10, 9 * 30 + 10, 24, strOut, RED);
	}

	uint32_t read_32b_num = 0;
	pAddr = (uint32_t *)(SRAM_ADDR_BEGIN + 0x100);
	if (HAL_SRAM_Read_32b(&hsram3, pAddr, &read_32b_num, 1) == HAL_OK) {
		lcd_show_str(10, 10 * 30 + 10, 24, "Read 32b random num at 0x6800 0100 ", RED);
		uint8_t tempStr[30];
		sprintf(tempStr, "0x%08X", read_32b_num);
		lcd_show_str(10, 11 * 30 + 10, 24, tempStr, RED);
	}
}

void SRAM_WriteByPointer() {
	lcd_show_str(10, 8 * 30 + 10, 24, "Write five uint16_t numbers", RED);
	lcd_show_str(10, 9 * 30 + 10, 24, "start from 0x68080000", RED);

	uint16_t num_to_write = 1000;
	uint16_t *pAddr_16b = (uint16_t *)(SRAM_ADDR_HALF);

	uint8_t tempStr[30];
	sprintf(tempStr, "");

	for (uint8_t i = 0; i < 5; ++i) {
		num_to_write += 5;
		*pAddr_16b = num_to_write;
		pAddr_16b++;
		sprintf(tempStr, "%s%d ", tempStr, num_to_write);
	}
	lcd_show_str(10, 10 * 30 + 10, 24, tempStr, RED);
}

void SRAM_ReadByPointer() {
	lcd_show_str(10, 8 * 30 + 10, 24, "Read five uint16_t numbers ", RED);
	lcd_show_str(10, 9 * 30 + 10, 24, "start from 0x68080000", RED);

	uint16_t num_to_read = 0;
	uint16_t *pAddr_16b = (uint16_t *)(SRAM_ADDR_HALF);
	uint8_t tempStr[30];
	sprintf(tempStr, "");
	for (uint8_t i = 0; i < 5; ++i) {
		num_to_read = *pAddr_16b;
		pAddr_16b++;
		sprintf(tempStr, "%s%d ", tempStr, num_to_read);
	}
	lcd_show_str(10, 10 * 30 + 10, 24, tempStr, RED);
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
