################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Service/Strings/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/PWM/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/DELAY/subdir.mk
-include ECUAL/LED/subdir.mk
-include ECUAL/KEYPAD/subdir.mk
-include ECUAL/BTN/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
UART_TASK2.lss \

FLASH_IMAGE += \
UART_TASK2.hex \

EEPROM_IMAGE += \
UART_TASK2.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: UART_TASK2.elf secondary-outputs

# Tool invocations
UART_TASK2.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,UART_TASK2.map -mmcu=atmega32 -o "UART_TASK2.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

UART_TASK2.lss: UART_TASK2.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S UART_TASK2.elf  >"UART_TASK2.lss"
	@echo 'Finished building: $@'
	@echo ' '

UART_TASK2.hex: UART_TASK2.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex UART_TASK2.elf  "UART_TASK2.hex"
	@echo 'Finished building: $@'
	@echo ' '

UART_TASK2.eep: UART_TASK2.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex UART_TASK2.elf  "UART_TASK2.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: UART_TASK2.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t UART_TASK2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) UART_TASK2.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
