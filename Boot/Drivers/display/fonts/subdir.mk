################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/display/fonts/PHanFont.c \
../Drivers/display/fonts/PHanFontEng.c \
../Drivers/display/fonts/PHan_Lib.c 

C_DEPS += \
./Drivers/display/fonts/PHanFont.d \
./Drivers/display/fonts/PHanFontEng.d \
./Drivers/display/fonts/PHan_Lib.d 

OBJS += \
./Drivers/display/fonts/PHanFont.o \
./Drivers/display/fonts/PHanFontEng.o \
./Drivers/display/fonts/PHan_Lib.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/display/fonts/PHanFont.o: ../Drivers/display/fonts/PHanFont.c Drivers/display/fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/display/fonts/PHanFont.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/display/fonts/PHanFontEng.o: ../Drivers/display/fonts/PHanFontEng.c Drivers/display/fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/display/fonts/PHanFontEng.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/display/fonts/PHan_Lib.o: ../Drivers/display/fonts/PHan_Lib.c Drivers/display/fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/display/fonts/PHan_Lib.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

