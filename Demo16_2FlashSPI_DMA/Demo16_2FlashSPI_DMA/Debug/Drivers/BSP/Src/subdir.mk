################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Src/keyled.c \
../Drivers/BSP/Src/lcd.c \
../Drivers/BSP/Src/w25flash.c 

OBJS += \
./Drivers/BSP/Src/keyled.o \
./Drivers/BSP/Src/lcd.o \
./Drivers/BSP/Src/w25flash.o 

C_DEPS += \
./Drivers/BSP/Src/keyled.d \
./Drivers/BSP/Src/lcd.d \
./Drivers/BSP/Src/w25flash.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Src/%.o Drivers/BSP/Src/%.su: ../Drivers/BSP/Src/%.c Drivers/BSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Src

clean-Drivers-2f-BSP-2f-Src:
	-$(RM) ./Drivers/BSP/Src/keyled.d ./Drivers/BSP/Src/keyled.o ./Drivers/BSP/Src/keyled.su ./Drivers/BSP/Src/lcd.d ./Drivers/BSP/Src/lcd.o ./Drivers/BSP/Src/lcd.su ./Drivers/BSP/Src/w25flash.d ./Drivers/BSP/Src/w25flash.o ./Drivers/BSP/Src/w25flash.su

.PHONY: clean-Drivers-2f-BSP-2f-Src

