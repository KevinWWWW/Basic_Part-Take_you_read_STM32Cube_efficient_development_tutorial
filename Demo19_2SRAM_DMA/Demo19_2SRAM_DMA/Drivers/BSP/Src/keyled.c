#include "keyled.h"

KEYS ScanPressedKey(uint32_t timeout)
{
	uint32_t tickstart = HAL_GetTick();
	const uint32_t btnDelay = 20;
	while (1)
	{
#ifdef KeyRight_Pin
		if (HAL_GPIO_ReadPin(KeyRight_GPIO_Port, KeyRight_Pin) == GPIO_PIN_RESET)
		{
			HAL_Delay(btnDelay);
			if (HAL_GPIO_ReadPin(KeyRight_GPIO_Port, KeyRight_Pin) == GPIO_PIN_RESET)
				return KEY_RIGHT;
		}
#endif
#ifdef KeyDown_Pin
		if (HAL_GPIO_ReadPin(KeyDown_GPIO_Port, KeyDown_Pin) == GPIO_PIN_RESET)
		{
			HAL_Delay(btnDelay);
			if (HAL_GPIO_ReadPin(KeyDown_GPIO_Port, KeyDown_Pin) == GPIO_PIN_RESET)
				return KEY_DOWN;
		}
#endif
#ifdef KeyLeft_Pin
		if (HAL_GPIO_ReadPin(KeyLeft_GPIO_Port, KeyLeft_Pin) == GPIO_PIN_RESET)
		{
			HAL_Delay(btnDelay);
			if (HAL_GPIO_ReadPin(KeyLeft_GPIO_Port, KeyLeft_Pin) == GPIO_PIN_RESET)
				return KEY_LEFT;
		}
#endif
#ifdef KeyUp_Pin
		if (HAL_GPIO_ReadPin(KeyUp_GPIO_Port, KeyUp_Pin) == GPIO_PIN_SET)
		{
			HAL_Delay(btnDelay);
			if (HAL_GPIO_ReadPin(KeyUp_GPIO_Port, KeyUp_Pin) == GPIO_PIN_SET)
				return KEY_UP;
		}
#endif
		if (timeout != KEY_WAIT_ALWAYS) {
			if ((HAL_GetTick() - tickstart) > timeout)
				break;
		}
	}
	return KEY_NONE;
}
