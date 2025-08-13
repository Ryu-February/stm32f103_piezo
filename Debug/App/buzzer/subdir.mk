################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/buzzer/buzzer.c 

OBJS += \
./App/buzzer/buzzer.o 

C_DEPS += \
./App/buzzer/buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
App/buzzer/%.o App/buzzer/%.su App/buzzer/%.cyclo: ../App/buzzer/%.c App/buzzer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Workspace/STM32WB50_HANGIL/STM32F103_Piezo/App/ap" -I"C:/Workspace/STM32WB50_HANGIL/STM32F103_Piezo/App/buzzer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-App-2f-buzzer

clean-App-2f-buzzer:
	-$(RM) ./App/buzzer/buzzer.cyclo ./App/buzzer/buzzer.d ./App/buzzer/buzzer.o ./App/buzzer/buzzer.su

.PHONY: clean-App-2f-buzzer

