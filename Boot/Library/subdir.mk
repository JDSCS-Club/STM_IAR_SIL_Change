################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/QBuf.c \
../Library/VerInfo.c \
../Library/adc.c \
../Library/adpcm.c \
../Library/audio.c \
../Library/bootloader.c \
../Library/cli.c \
../Library/eeprom.c \
../Library/flash_if.c \
../Library/iap_common.c \
../Library/iap_menu.c \
../Library/serial.c \
../Library/unicode.c \
../Library/version.c \
../Library/ymodem.c 

C_DEPS += \
./Library/QBuf.d \
./Library/VerInfo.d \
./Library/adc.d \
./Library/adpcm.d \
./Library/audio.d \
./Library/bootloader.d \
./Library/cli.d \
./Library/eeprom.d \
./Library/flash_if.d \
./Library/iap_common.d \
./Library/iap_menu.d \
./Library/serial.d \
./Library/unicode.d \
./Library/version.d \
./Library/ymodem.d 

OBJS += \
./Library/QBuf.o \
./Library/VerInfo.o \
./Library/adc.o \
./Library/adpcm.o \
./Library/audio.o \
./Library/bootloader.o \
./Library/cli.o \
./Library/eeprom.o \
./Library/flash_if.o \
./Library/iap_common.o \
./Library/iap_menu.o \
./Library/serial.o \
./Library/unicode.o \
./Library/version.o \
./Library/ymodem.o 


# Each subdirectory must supply rules for building sources it contributes
Library/QBuf.o: ../Library/QBuf.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/QBuf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/VerInfo.o: ../Library/VerInfo.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/VerInfo.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/adc.o: ../Library/adc.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/adpcm.o: ../Library/adpcm.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/adpcm.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/audio.o: ../Library/audio.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/audio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/bootloader.o: ../Library/bootloader.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/bootloader.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/cli.o: ../Library/cli.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/cli.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/eeprom.o: ../Library/eeprom.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/eeprom.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/flash_if.o: ../Library/flash_if.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/flash_if.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/iap_common.o: ../Library/iap_common.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/iap_common.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/iap_menu.o: ../Library/iap_menu.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/iap_menu.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/serial.o: ../Library/serial.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/serial.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/unicode.o: ../Library/unicode.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/unicode.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/version.o: ../Library/version.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/version.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Library/ymodem.o: ../Library/ymodem.c Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DHAVE_CONFIG_H -DDEBUG -DSTM32F407xx -DUSE_BOOTLOADER -c -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Core/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Library -I../Drivers/display -I../Drivers/display/fonts -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Library/ymodem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

