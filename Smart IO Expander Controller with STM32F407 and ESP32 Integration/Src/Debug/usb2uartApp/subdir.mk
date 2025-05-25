################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb2uartApp/usb2uartApp.c 

OBJS += \
./usb2uartApp/usb2uartApp.o 

C_DEPS += \
./usb2uartApp/usb2uartApp.d 


# Each subdirectory must supply rules for building sources it contributes
usb2uartApp/%.o usb2uartApp/%.su usb2uartApp/%.cyclo: ../usb2uartApp/%.c usb2uartApp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/mjayakumar/VVDN_BU_TRAINING/STM32/Program/PROJECT_01/ioExpander" -I"/home/mjayakumar/VVDN_BU_TRAINING/STM32/Program/PROJECT_01/usb2uartApp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-usb2uartApp

clean-usb2uartApp:
	-$(RM) ./usb2uartApp/usb2uartApp.cyclo ./usb2uartApp/usb2uartApp.d ./usb2uartApp/usb2uartApp.o ./usb2uartApp/usb2uartApp.su

.PHONY: clean-usb2uartApp

