################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ioExpander/ioExpander.c 

OBJS += \
./ioExpander/ioExpander.o 

C_DEPS += \
./ioExpander/ioExpander.d 


# Each subdirectory must supply rules for building sources it contributes
ioExpander/%.o ioExpander/%.su ioExpander/%.cyclo: ../ioExpander/%.c ioExpander/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/mjayakumar/VVDN_BU_TRAINING/STM32/Program/PROJECT_01/ioExpander" -I"/home/mjayakumar/VVDN_BU_TRAINING/STM32/Program/PROJECT_01/usb2uartApp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ioExpander

clean-ioExpander:
	-$(RM) ./ioExpander/ioExpander.cyclo ./ioExpander/ioExpander.d ./ioExpander/ioExpander.o ./ioExpander/ioExpander.su

.PHONY: clean-ioExpander

