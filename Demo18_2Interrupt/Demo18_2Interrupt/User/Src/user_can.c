/*
 * user_can.c
 *
 *  Created on: 2023年8月6日
 *      Author: 71492
 */

#include "user_can.h"

HAL_StatusTypeDef CAN_SetFilters() {
	CAN_FilterTypeDef canFilter;

	// 1. 设置FIFO0的筛选器
	canFilter.FilterBank = 0;
	canFilter.FilterMode = CAN_FILTERMODE_IDMASK;
	canFilter.FilterScale = CAN_FILTERSCALE_32BIT;

	canFilter.FilterIdHigh = 0x0020;
	canFilter.FilterIdLow = 0x0000;
	canFilter.FilterMaskIdHigh = 0x0020;
	canFilter.FilterMaskIdLow = 0x0000;

	canFilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	canFilter.FilterActivation = CAN_FILTER_ENABLE;
	canFilter.SlaveStartFilterBank = 14;
	HAL_StatusTypeDef result = HAL_CAN_ConfigFilter(&hcan1, &canFilter);
	if (result != HAL_OK) {
		return result;
	}

	// 2. 设置FIFO1的筛选器
	canFilter.FilterBank = 1;

	canFilter.FilterIdHigh = 0x0000;
	canFilter.FilterIdLow = 0x0000;
	canFilter.FilterMaskIdHigh = 0x0000;
	canFilter.FilterMaskIdLow = 0x0000;

	canFilter.FilterFIFOAssignment = CAN_FILTER_FIFO1;
	result = HAL_CAN_ConfigFilter(&hcan1, &canFilter);
	return result;
}

void CAN_TestPoll(uint8_t msgID, uint8_t frameType) {
	// 1. 发送消息
	uint8_t TxData[8];
	TxData[0] = msgID;
	TxData[1] = msgID + 11;

	CAN_TxHeaderTypeDef TxHeader;
	TxHeader.StdId = msgID;
	TxHeader.RTR = frameType;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = 2;
	TxHeader.TransmitGlobalTime = DISABLE;

	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) < 1) {
		;
	}

	uint32_t TxMailbox;
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
		lcd_show_str(10, 10 + 7 * 30, 24, "Send to mailbox error", RED);
		  return;
	}
	uint8_t tempStr[30];
	sprintf(tempStr, "Send MsgID = %d", msgID);
	lcd_show_str(10, 10 + 7 * 30, 24, tempStr, RED);

	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 3) {
		;
	}

	// 2.轮询方式接收消息
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData[8];
	HAL_Delay(1);
	if (HAL_CAN_GetRxFifoFillLevel(&hcan1, CAN_RX_FIFO0) != 1) {
		lcd_show_str(10, 10 + 8 * 30, 24, "Message is not received", RED);
		return;
	}
	lcd_show_str(10, 10 + 8 * 30, 24, "Message is received", RED);

	if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK) {
		sprintf(tempStr, "StdID = %d", RxHeader.StdId);
		lcd_show_str(10, 10 + 9 * 30, 24, tempStr, RED);

		sprintf(tempStr, "RTR(0=Data, 2=Remote) = %d", RxHeader.RTR);
		lcd_show_str(10, 10 + 10 * 30, 24, tempStr, RED);

		sprintf(tempStr, "IDE(0=Std, 4=Ext) = %d", RxHeader.IDE);
		lcd_show_str(10, 10 + 11 * 30, 24, tempStr, RED);

		sprintf(tempStr, "DLC(Data Length) = %d", RxHeader.DLC);
		lcd_show_str(10, 10 + 12 * 30, 24, tempStr, RED);

		if (TxHeader.RTR == CAN_RTR_DATA) {
			sprintf(tempStr, "Data[0] = %d", RxData[0]);
			lcd_show_str(10, 10 + 13 * 30, 24, tempStr, RED);

			sprintf(tempStr, "Data[1] = %d", RxData[1]);
			lcd_show_str(10, 10 + 14 * 30, 24, tempStr, RED);
		}
	}
}

void CAN_SendMsg(uint8_t msgID, uint8_t frameType) {
	CAN_TxHeaderTypeDef TxHeader;
	TxHeader.StdId = msgID;
	TxHeader.RTR = frameType;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.DLC = 4;
	TxHeader.TransmitGlobalTime = DISABLE;

	uint32_t random32bit;
	HAL_RNG_GenerateRandomNumber(&hrng, &random32bit);

	uint8_t TxData[8];
	TxData[3] = random32bit & 0x000000FF;
	TxData[2] = (random32bit & 0x0000FF00) >> 8;
	TxData[1] = (random32bit & 0x00FF0000) >> 16;
	TxData[0] = (random32bit & 0xFF000000) >> 24;

	while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) < 1) {
		;
	}

	uint8_t tempStr[30];
	sprintf(tempStr, "Send MsgID = %d", msgID);
	lcd_show_str(10, 10 + 7 * 30, 24, tempStr, RED);
	uint32_t TxMailbox;
	if (HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
		lcd_show_str(10, 10 + 8 * 30, 24, "Send to mailbox error", RED);
		  return;
	}
}

void CAN_ReadMsg(uint32_t FIFO_num) {
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t RxData[8];

	if (FIFO_num == CAN_RX_FIFO0) {
		lcd_show_str(10, 10 + 9 * 30, 24, "Message received by FIFO0", RED);
		if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK) {
			lcd_show_str(10, 10 + 10 * 30, 24, "Read FIFO0 error", RED);
			return;
		}
	} else {
		lcd_show_str(10, 10 + 9 * 30, 24, "Message received by FIFO1", RED);
		if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO1, &RxHeader, RxData) != HAL_OK) {
			lcd_show_str(10, 10 + 10 * 30, 24, "Read FIFO1 error", RED);
			return;
		}
	}
	uint8_t tempStr[30];

	sprintf(tempStr, "StdID = %d", RxHeader.StdId);
	lcd_show_str(10, 10 + 11 * 30, 24, tempStr, RED);

	sprintf(tempStr, "RTR(0=Data, 2=Remote) = %d", RxHeader.RTR);
	lcd_show_str(10, 10 + 12 * 30, 24, tempStr, RED);

	sprintf(tempStr, "IDE(0=Std, 4=Ext) = %d", RxHeader.IDE);
	lcd_show_str(10, 10 + 13 * 30, 24, tempStr, RED);

	sprintf(tempStr, "DLC(Data Length) = %d", RxHeader.DLC);
	lcd_show_str(10, 10 + 14 * 30, 24, tempStr, RED);

	sprintf(tempStr, "Data = %02X %02X %02X %02X", RxData[0], RxData[1], RxData[2], RxData[3]);
	lcd_show_str(10, 10 + 15 * 30, 24, tempStr, RED);

	lcd_show_str(10, 10 + 16 * 30, 24, "** Reselect menu or reset **", RED);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	CAN_ReadMsg(CAN_RX_FIFO0);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	CAN_ReadMsg(CAN_RX_FIFO1);
}



















