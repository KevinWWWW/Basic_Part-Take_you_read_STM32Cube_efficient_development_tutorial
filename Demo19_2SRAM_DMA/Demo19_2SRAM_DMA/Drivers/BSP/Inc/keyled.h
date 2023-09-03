#ifndef KEYLED_H_
#define KEYLED_H_

#include "main.h"

typedef enum {
	KEY_NONE = 0,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN
} KEYS;

#define KEY_WAIT_ALWAYS		0

KEYS ScanPressedKey(uint32_t timeout);

#ifdef	LED1_Pin
	#define LED1_Toggle()	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin)
	#define LED1_OFF()		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
	#define LED1_ON()		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#endif

#ifdef	LED2_Pin
	#define LED2_Toggle()	HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin)
	#define LED2_OFF()		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET)
	#define LED2_ON()		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET)
#endif

#ifdef	Buzzer_Pin
	#define Buzzer_Toggle()	HAL_GPIO_TogglePin(Buzzer_GPIO_Port, Buzzer_Pin)
	#define Buzzer_ON()		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET)
	#define Buzzer_OFF()	HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET)
#endif

#endif // KEYLED_H_
