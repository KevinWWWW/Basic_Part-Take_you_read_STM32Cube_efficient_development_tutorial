/*
 * user_can.h
 *
 *  Created on: 2023年8月6日
 *      Author: 71492
 */

#ifndef INC_USER_CAN_H_
#define INC_USER_CAN_H_

#include "main.h"

HAL_StatusTypeDef CAN_SetFilters();
void CAN_TestPoll(uint8_t msgID, uint8_t frameType);
void CAN_SendMsg(uint8_t msgID, uint8_t frametype);
void CAN_ReadMsg(uint32_t FIFO_num);

#endif /* INC_USER_CAN_H_ */
