/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
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
#include "usart.h"

/* USER CODE BEGIN 0 */
#include <string.h>
#include <stdio.h>
#include "lcd.h"
#include "rtc.h"
#define UART_TIMEOUT	400
#define PRO_BUF_LEN		200
uint8_t RxProBuf[PRO_BUF_LEN];
uint8_t isUploadTime = 1;

/* USER CODE END 0 */

UART_HandleTypeDef huart1;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 57600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void Uart_RxAgain(UART_HandleTypeDef *huart) {
	HAL_UARTEx_ReceiveToIdle_IT(huart, RxProBuf, PRO_BUF_LEN);
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  if (huart->Instance == USART1) {
	  if (RxProBuf[0] == '#') {
		  Cmd_Process();
	  }

	  RxProBuf[Size++] = '\r';
	  RxProBuf[Size++] = '\n';
	  RxProBuf[Size++] = '\0';

	  lcd_show_str(10, 10, 16, RxProBuf, RED);
	  HAL_UART_Transmit(&huart1, RxProBuf, Size, UART_TIMEOUT);
  }
}

void Cmd_Process() {
	uint16_t value = 0;
	uint8_t index = 2;
	while(1) {
		if (RxProBuf[index] == ';') {
			break;
		}
		value *= 10;
		value += (RxProBuf[index] - '0');
		index++;
	}


	if (RxProBuf[1] = 'U') {
		isUploadTime = value;
		return;
	}

	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK) {
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		sTime.DayLightSaving = 0;
		sTime.StoreOperation = 0;

		if (RxProBuf[1] = 'H') {
			sTime.Hours = value;
		} else if (RxProBuf[1] = 'M') {
			sTime.Minutes = value;
		} else if (RxProBuf[1] = 'S') {
			sTime.Seconds = value;
		}
		HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	}
}

void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
	RTC_TimeTypeDef sTime;
	RTC_DateTypeDef sDate;
	if (HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK) {
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		uint8_t timeStr[30];
        sprintf(timeStr, "%02d:%02d:%02d\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
		lcd_show_str(30, 10, 16, timeStr, RED);
		if (isUploadTime) {
			HAL_UART_Transmit(&huart1, timeStr, strlen(timeStr), UART_TIMEOUT);
		}
	}
}
/* USER CODE END 1 */
