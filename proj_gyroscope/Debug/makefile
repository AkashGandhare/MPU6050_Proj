################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MP6050/subdir.mk
-include Drivers/STM32F0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
proj_gyroscope.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
proj_gyroscope.list \

OBJCOPY_BIN += \
proj_gyroscope.bin \


# All Target
all: proj_gyroscope.elf secondary-outputs

# Tool invocations
proj_gyroscope.elf: $(OBJS) $(USER_OBJS) C:\Users\akash\STM32CubeIDE\workspace_1.3.0\proj_gyroscope\STM32F070RBTX_FLASH.ld
	arm-none-eabi-gcc -o "proj_gyroscope.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0 -T"C:\Users\akash\STM32CubeIDE\workspace_1.3.0\proj_gyroscope\STM32F070RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="proj_gyroscope.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

proj_gyroscope.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "proj_gyroscope.list"
	@echo 'Finished building: $@'
	@echo ' '

proj_gyroscope.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "proj_gyroscope.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
