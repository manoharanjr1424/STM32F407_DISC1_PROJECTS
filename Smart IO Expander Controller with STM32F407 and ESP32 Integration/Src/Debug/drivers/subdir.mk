################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/gpio.c \
../drivers/i2c.c \
../drivers/interrupt.c \
../drivers/mcu.c \
../drivers/timer.c \
../drivers/uart.c 

OBJS += \
./drivers/gpio.o \
./drivers/i2c.o \
./drivers/interrupt.o \
./drivers/mcu.o \
./drivers/timer.o \
./drivers/uart.o 

C_DEPS += \
./drivers/gpio.d \
./drivers/i2c.d \
./drivers/interrupt.d \
./drivers/mcu.d \
./drivers/timer.d \
./drivers/uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o drivers/%.su drivers/%.cyclo: ../drivers/%.c drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"/home/mjayakumar/VVDN_BU_TRAINING/STM32/Program/PROJECT_01/ioExpander" -I"/home/mjayakumar/VVDN_BU_TRAINING/STM32/Program/PROJECT_01/usb2uartApp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/gpio.cyclo ./drivers/gpio.d ./drivers/gpio.o ./drivers/gpio.su ./drivers/i2c.cyclo ./drivers/i2c.d ./drivers/i2c.o ./drivers/i2c.su ./drivers/interrupt.cyclo ./drivers/interrupt.d ./drivers/interrupt.o ./drivers/interrupt.su ./drivers/mcu.cyclo ./drivers/mcu.d ./drivers/mcu.o ./drivers/mcu.su ./drivers/timer.cyclo ./drivers/timer.d ./drivers/timer.o ./drivers/timer.su ./drivers/uart.cyclo ./drivers/uart.d ./drivers/uart.o ./drivers/uart.su

.PHONY: clean-drivers

