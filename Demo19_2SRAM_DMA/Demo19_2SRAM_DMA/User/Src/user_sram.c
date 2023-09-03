#include "user_sram.h"

uint32_t rxBuffer[COUNT];
bool DMA_Direction_is_Write = true;
bool DMA_Busy = false;

void SRAM_WriteDirectly() {
	lcd_show_str(10, 7 * 30 + 10, 24, "Wirte 32bit array directly", RED);

	uint32_t txBuffer[COUNT];
	uint32_t value = 1000;
	uint8_t tempStr[30];
	sprintf(tempStr, "");
	for (uint8_t i = 0; i < COUNT; ++i) {
		txBuffer[i] = value;
		value += 5;
		sprintf(tempStr, "%s%d ", tempStr, value);
	}
	lcd_show_str(10, 8 * 30 + 10, 24, tempStr, RED);

	uint32_t *pAddress = (uint32_t *)SRAM_ADDR_BEGIN;
	if (HAL_SRAM_Write_32b(&hsram3, pAddress, txBuffer, COUNT) == HAL_OK) {
		lcd_show_str(10, 9 * 30 + 10, 24, "Array is written successfully", RED);
	}
}

void SRAM_WriteByDMA() {

	lcd_show_str(10, 7 * 30 + 10, 24, "Wirte 32bit array by DMA", RED);

	uint32_t txBuffer[COUNT];
	uint32_t value = 3000;
	uint8_t tempStr[30];
	sprintf(tempStr, "");
	for (uint8_t i = 0; i < COUNT; ++i) {
		txBuffer[i] = value;
		value += 6;
		sprintf(tempStr, "%s%d ", tempStr, value);
	}
	lcd_show_str(10, 8 * 30 + 10, 24, tempStr, RED);

	DMA_Direction_is_Write = true;
	DMA_Busy = true;
	uint32_t *pAddress = (uint32_t *)SRAM_ADDR_BEGIN;
	HAL_SRAM_Write_DMA(&hsram3, pAddress, txBuffer, COUNT);
}

void SRAM_ReadByDMA() {
	lcd_show_str(10, 7 * 30 + 10, 24, "Read 32bit array by DMA", RED);
	uint32_t *pAddress = (uint32_t *)SRAM_ADDR_BEGIN;
	DMA_Direction_is_Write = false;
	DMA_Busy = true;
	HAL_SRAM_Read_DMA(&hsram3, pAddress, rxBuffer, COUNT);
}

void HAL_SRAM_DMA_XferCpltCallback(DMA_HandleTypeDef *hdma) {
	if (DMA_Direction_is_Write) {
		lcd_show_str(10, 9 * 30 + 10, 24, "Written by DMA complete", RED);
	} else {
		lcd_show_str(10, 8 * 30 + 10, 24, "Read by DMA complete", RED);

		uint8_t tempStr[30];
		sprintf(tempStr, "");
		for (uint8_t i = 0; i < COUNT; ++i) {
			sprintf(tempStr, "%s%d ", tempStr, rxBuffer[i]);
		}
		lcd_show_str(10, 9 * 30 + 10, 24, tempStr, RED);
	}
	DMA_Busy = false;
}














