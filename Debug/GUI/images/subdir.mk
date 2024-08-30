################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GUI/images/01dPNG.c \
../GUI/images/01nPNG.c \
../GUI/images/02dPNG.c \
../GUI/images/02nPNG.c \
../GUI/images/03dnPNG.c \
../GUI/images/04dnPNG.c \
../GUI/images/09dnPNG.c \
../GUI/images/10dPNG.c \
../GUI/images/10nPNG.c \
../GUI/images/11dnPNG.c \
../GUI/images/13dnPNG.c \
../GUI/images/50dnPNG.c \
../GUI/images/bulbPNG.c \
../GUI/images/crossPNG.c \
../GUI/images/fanPNG.c \
../GUI/images/menuPNG.c \
../GUI/images/noWifiPNG.c \
../GUI/images/tickPNG.c \
../GUI/images/wifiPNG.c 

OBJS += \
./GUI/images/01dPNG.o \
./GUI/images/01nPNG.o \
./GUI/images/02dPNG.o \
./GUI/images/02nPNG.o \
./GUI/images/03dnPNG.o \
./GUI/images/04dnPNG.o \
./GUI/images/09dnPNG.o \
./GUI/images/10dPNG.o \
./GUI/images/10nPNG.o \
./GUI/images/11dnPNG.o \
./GUI/images/13dnPNG.o \
./GUI/images/50dnPNG.o \
./GUI/images/bulbPNG.o \
./GUI/images/crossPNG.o \
./GUI/images/fanPNG.o \
./GUI/images/menuPNG.o \
./GUI/images/noWifiPNG.o \
./GUI/images/tickPNG.o \
./GUI/images/wifiPNG.o 

C_DEPS += \
./GUI/images/01dPNG.d \
./GUI/images/01nPNG.d \
./GUI/images/02dPNG.d \
./GUI/images/02nPNG.d \
./GUI/images/03dnPNG.d \
./GUI/images/04dnPNG.d \
./GUI/images/09dnPNG.d \
./GUI/images/10dPNG.d \
./GUI/images/10nPNG.d \
./GUI/images/11dnPNG.d \
./GUI/images/13dnPNG.d \
./GUI/images/50dnPNG.d \
./GUI/images/bulbPNG.d \
./GUI/images/crossPNG.d \
./GUI/images/fanPNG.d \
./GUI/images/menuPNG.d \
./GUI/images/noWifiPNG.d \
./GUI/images/tickPNG.d \
./GUI/images/wifiPNG.d 


# Each subdirectory must supply rules for building sources it contributes
GUI/images/%.o GUI/images/%.su GUI/images/%.cyclo: ../GUI/images/%.c GUI/images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I"E:/Final Projects/SMARTHomeFreeRTOS/FreeRTOS" -I"E:/Final Projects/SMARTHomeFreeRTOS/ESP" -I"E:/Final Projects/SMARTHomeFreeRTOS/GUI" -I"E:/Final Projects/SMARTHomeFreeRTOS/GUI/images" -I"E:/Final Projects/SMARTHomeFreeRTOS/FreeRTOS/include" -I"E:/Final Projects/SMARTHomeFreeRTOS/FreeRTOS/portable/GCC/ARM_CM4F" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GUI-2f-images

clean-GUI-2f-images:
	-$(RM) ./GUI/images/01dPNG.cyclo ./GUI/images/01dPNG.d ./GUI/images/01dPNG.o ./GUI/images/01dPNG.su ./GUI/images/01nPNG.cyclo ./GUI/images/01nPNG.d ./GUI/images/01nPNG.o ./GUI/images/01nPNG.su ./GUI/images/02dPNG.cyclo ./GUI/images/02dPNG.d ./GUI/images/02dPNG.o ./GUI/images/02dPNG.su ./GUI/images/02nPNG.cyclo ./GUI/images/02nPNG.d ./GUI/images/02nPNG.o ./GUI/images/02nPNG.su ./GUI/images/03dnPNG.cyclo ./GUI/images/03dnPNG.d ./GUI/images/03dnPNG.o ./GUI/images/03dnPNG.su ./GUI/images/04dnPNG.cyclo ./GUI/images/04dnPNG.d ./GUI/images/04dnPNG.o ./GUI/images/04dnPNG.su ./GUI/images/09dnPNG.cyclo ./GUI/images/09dnPNG.d ./GUI/images/09dnPNG.o ./GUI/images/09dnPNG.su ./GUI/images/10dPNG.cyclo ./GUI/images/10dPNG.d ./GUI/images/10dPNG.o ./GUI/images/10dPNG.su ./GUI/images/10nPNG.cyclo ./GUI/images/10nPNG.d ./GUI/images/10nPNG.o ./GUI/images/10nPNG.su ./GUI/images/11dnPNG.cyclo ./GUI/images/11dnPNG.d ./GUI/images/11dnPNG.o ./GUI/images/11dnPNG.su ./GUI/images/13dnPNG.cyclo ./GUI/images/13dnPNG.d ./GUI/images/13dnPNG.o ./GUI/images/13dnPNG.su ./GUI/images/50dnPNG.cyclo ./GUI/images/50dnPNG.d ./GUI/images/50dnPNG.o ./GUI/images/50dnPNG.su ./GUI/images/bulbPNG.cyclo ./GUI/images/bulbPNG.d ./GUI/images/bulbPNG.o ./GUI/images/bulbPNG.su ./GUI/images/crossPNG.cyclo ./GUI/images/crossPNG.d ./GUI/images/crossPNG.o ./GUI/images/crossPNG.su ./GUI/images/fanPNG.cyclo ./GUI/images/fanPNG.d ./GUI/images/fanPNG.o ./GUI/images/fanPNG.su ./GUI/images/menuPNG.cyclo ./GUI/images/menuPNG.d ./GUI/images/menuPNG.o ./GUI/images/menuPNG.su ./GUI/images/noWifiPNG.cyclo ./GUI/images/noWifiPNG.d ./GUI/images/noWifiPNG.o ./GUI/images/noWifiPNG.su ./GUI/images/tickPNG.cyclo ./GUI/images/tickPNG.d ./GUI/images/tickPNG.o ./GUI/images/tickPNG.su ./GUI/images/wifiPNG.cyclo ./GUI/images/wifiPNG.d ./GUI/images/wifiPNG.o ./GUI/images/wifiPNG.su

.PHONY: clean-GUI-2f-images

