################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ESP/circularBuffer.c \
../ESP/esp.c 

OBJS += \
./ESP/circularBuffer.o \
./ESP/esp.o 

C_DEPS += \
./ESP/circularBuffer.d \
./ESP/esp.d 


# Each subdirectory must supply rules for building sources it contributes
ESP/%.o ESP/%.su ESP/%.cyclo: ../ESP/%.c ESP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"E:/Final Projects/SMARTHomeFreeRTOS/FreeRTOS" -I"E:/Final Projects/SMARTHomeFreeRTOS/ESP" -I"E:/Final Projects/SMARTHomeFreeRTOS/GUI" -I"E:/Final Projects/SMARTHomeFreeRTOS/GUI/images" -I"E:/Final Projects/SMARTHomeFreeRTOS/FreeRTOS/include" -I"E:/Final Projects/SMARTHomeFreeRTOS/FreeRTOS/portable/GCC/ARM_CM4F" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ESP

clean-ESP:
	-$(RM) ./ESP/circularBuffer.cyclo ./ESP/circularBuffer.d ./ESP/circularBuffer.o ./ESP/circularBuffer.su ./ESP/esp.cyclo ./ESP/esp.d ./ESP/esp.o ./ESP/esp.su

.PHONY: clean-ESP

