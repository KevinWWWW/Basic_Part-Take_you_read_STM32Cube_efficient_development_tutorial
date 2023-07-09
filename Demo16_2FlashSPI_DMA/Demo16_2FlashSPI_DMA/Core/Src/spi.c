/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
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
#include "spi.h"

/* USER CODE BEGIN 0 */
#include "lcd.h"
#include "w25flash.h"
#include <string.h>
#include <stdio.h>

uint8_t bufPageRead[FLASH_PAGE_SIZE];
uint8_t bufPageWrite[FLASH_PAGE_SIZE];
/* USER CODE END 0 */

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_tx;
DMA_HandleTypeDef hdma_spi1_rx;

/* SPI1 init function */
void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

void HAL_SPI_MspInit(SPI_HandleTypeDef* spiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspInit 0 */

  /* USER CODE END SPI1_MspInit 0 */
    /* SPI1 clock enable */
    __HAL_RCC_SPI1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* SPI1 DMA Init */
    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA2_Stream3;
    hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(spiHandle,hdmatx,hdma_spi1_tx);

    /* SPI1_RX Init */
    hdma_spi1_rx.Instance = DMA2_Stream0;
    hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;
    hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi1_rx.Init.Mode = DMA_NORMAL;
    hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(spiHandle,hdmarx,hdma_spi1_rx);

  /* USER CODE BEGIN SPI1_MspInit 1 */

  /* USER CODE END SPI1_MspInit 1 */
  }
}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* spiHandle)
{

  if(spiHandle->Instance==SPI1)
  {
  /* USER CODE BEGIN SPI1_MspDeInit 0 */

  /* USER CODE END SPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SPI1_CLK_DISABLE();

    /**SPI1 GPIO Configuration
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);

    /* SPI1 DMA DeInit */
    HAL_DMA_DeInit(spiHandle->hdmatx);
    HAL_DMA_DeInit(spiHandle->hdmarx);
  /* USER CODE BEGIN SPI1_MspDeInit 1 */

  /* USER CODE END SPI1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void Flash_TestReadStatus() {
	uint16_t devID = Flash_ReadID();

	uint8_t tempStrDevID[30];
	sprintf(tempStrDevID, "Device ID = 0x%04X", devID);
	lcd_show_str(10, 2*30 + 10, 24, tempStrDevID, RED);

	switch (devID) {
	case 0xEF17:
		lcd_show_str(10, 3*30 + 10, 24, "The chip is: W25Q128", RED);
		break;
	case 0xC817:
		lcd_show_str(10, 3*30 + 10, 24, "The chip is: GD25Q128", RED);
		break;
	case 0x1C17:
		lcd_show_str(10, 3*30 + 10, 24, "The chip is: EN25Q128", RED);
		break;
	case 0x2018:
		lcd_show_str(10, 3*30 + 10, 24, "The chip is: N25Q128", RED);
		break;
	case 0x2017:
		lcd_show_str(10, 3*30 + 10, 24, "The chip is: XMN25QH128", RED);
		break;
	case 0xA117:
		lcd_show_str(10, 3*30 + 10, 24, "The chip is: FM25Q128", RED);
		break;
//	case 0x:
//		lcd_show_str(10, 3*30 + 10, 24, "The chip is: NM25Q128", RED);
//		break;
//	case 0x:
//		lcd_show_str(10, 3*30 + 10, 24, "The chip is: BY25Q128", RED);
//		break;
	default:
		lcd_show_str(10, 3*30 + 10, 24, "Unknown type", RED);
	}

	uint8_t tempStrSR1[30];
	sprintf(tempStrSR1, "Status Reg1 = 0x%X", Flash_ReadSR1());
	lcd_show_str(10, 4*30 + 10, 24, tempStrSR1, RED);

	uint8_t tempStrSR2[30];
	sprintf(tempStrSR2, "Status Reg2 = 0x%X", Flash_ReadSR2());
	lcd_show_str(10, 5*30 + 10, 24, tempStrSR2, RED);
}

void Flash_TestWrite() {
	uint8_t BlockNo = 0;
	uint8_t SubSectorNo = 0;
	uint8_t SubPageNo = 0;
	uint32_t memAddress = 0;
	memAddress = Flash_Addr_byBlockSectorPage(BlockNo, SubSectorNo, SubPageNo);
	uint8_t bufStr1[30] = "Hello from beginning";
	Flash_WriteInPage(memAddress, bufStr1, strlen(bufStr1) + 1);
	lcd_show_str(10, 11*30 + 10, 24, "Write in Page0:0", RED);
	lcd_show_str(10, 12*30 + 10, 24, bufStr1, RED);

	uint8_t bufStr2[30] = "Hello in page";
	Flash_WriteInPage(memAddress + 100, bufStr2, strlen(bufStr2) + 1);
	lcd_show_str(10, 13*30 + 10, 24, "Write in Page0:100", RED);
	lcd_show_str(10, 14*30 + 10, 24, bufStr2, RED);

	uint8_t bufPage[FLASH_PAGE_SIZE];
	for (uint16_t i = 0; i < FLASH_PAGE_SIZE; ++i) {
		bufPage[i] = i;
	}
	SubPageNo = 1;
	memAddress = Flash_Addr_byBlockSectorPage(BlockNo, SubSectorNo, SubPageNo);
	Flash_WriteInPage(memAddress, bufPage, FLASH_PAGE_SIZE);
	lcd_show_str(10, 15*30 + 10, 24, "Write 0~255 in Page1", RED);
}

void Flash_TestRead() {
	uint8_t BlockNo = 0;
	uint8_t SubSectorNo = 0;
	uint8_t SubPageNo = 0;
	uint32_t memAddress = Flash_Addr_byBlockSectorPage(BlockNo, SubSectorNo, SubPageNo);
	uint8_t bufStr[50];
	Flash_ReadBytes(memAddress, bufStr, 50);
	lcd_show_str(10, 11*30 + 10, 24, "Read in Page0:0 ", RED);
	lcd_show_str(10, 12*30 + 10, 24, bufStr, RED);

	Flash_ReadBytes(memAddress + 100, bufStr, 50);
	lcd_show_str(10, 13*30 + 10, 24, "Read in Page0:100 ", RED);
	lcd_show_str(10, 14*30 + 10, 24, bufStr, RED);

	SubPageNo = 1;
	memAddress = Flash_Addr_byBlockSectorPage(BlockNo, SubSectorNo, SubPageNo);
	uint8_t randData12 = Flash_ReadOneByte(memAddress + 12);
	uint8_t randData136 = Flash_ReadOneByte(memAddress + 136);
	uint8_t randData210 = Flash_ReadOneByte(memAddress + 210);
	uint8_t tempStrRandData[30];
	sprintf(tempStrRandData, "Page1[12]=%d,[136]=%d,[210]=%d",
			randData12, randData136, randData210);
	lcd_show_str(10, 15*30 + 10, 24, tempStrRandData, RED);
}

void Flash_TestWriteDMA() {
	uint8_t BlockNo = 0;
	uint8_t SubSectorNo = 0;
	uint8_t SubPageNo = 3;
	uint32_t memAddress = Flash_Addr_byBlockSectorPage(BlockNo, SubSectorNo, SubPageNo);

	for (uint16_t i = 0; i < FLASH_PAGE_SIZE; ++i) {
		bufPageRead[i] = i;
	}

	Flash_WriteInPage_DMA(memAddress, bufPageRead, FLASH_PAGE_SIZE);
	lcd_show_str(10, 11*30 + 10, 24, "Writing Page3 in DMA mode.", RED);
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
	__Deselect_Flash();	//CS=1
	Flash_Wait_Busy();
	lcd_show_str(10, 12*30 + 10, 24, "DMA Writing complete.", RED);
}

void Flash_TestReadDMA() {
	uint8_t BlockNo = 0;
	uint8_t SubSectorNo = 0;
	uint8_t SubPageNo = 3;
	uint32_t memAddress = Flash_Addr_byBlockSectorPage(BlockNo, SubSectorNo, SubPageNo);
	Flash_ReadBytes_DMA(memAddress, bufPageWrite, FLASH_PAGE_SIZE);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
	__Deselect_Flash();	//CS=1
	Flash_Wait_Busy();
	lcd_show_str(10, 11*30 + 10, 24, "DMA reading complete.", RED);

	uint8_t tempStr[50];
	sprintf(tempStr, "Page3[26] = %d, [205] = %d",
			bufPageWrite[26], bufPageWrite[205]);
	lcd_show_str(10, 12*30 + 10, 24, tempStr, RED);

}
/* USER CODE END 1 */
