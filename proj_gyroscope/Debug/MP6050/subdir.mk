################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MP6050/mp6050.c 

OBJS += \
./MP6050/mp6050.o 

C_DEPS += \
./MP6050/mp6050.d 


# Each subdirectory must supply rules for building sources it contributes
MP6050/mp6050.o: ../MP6050/mp6050.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DSTM32F070xB -DUSE_HAL_DRIVER -DDEBUG -c -I../MP6050 -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MP6050/mp6050.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

