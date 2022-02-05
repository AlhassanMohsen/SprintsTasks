################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SERVICE/Strings/subdir.mk
-include SERVICE/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/PWM/subdir.mk
-include MCAL/I2C/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/DELAY/subdir.mk
-include MCAL/ADC/subdir.mk
-include ECUAL/TEMP_SENSOR/subdir.mk
-include ECUAL/MOTOR/subdir.mk
-include ECUAL/LED/subdir.mk
-include ECUAL/LCD/subdir.mk
-include ECUAL/KEYPAD/subdir.mk
-include ECUAL/INTERFACE/subdir.mk
-include ECUAL/EEPROM/subdir.mk
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
CARD_ECU.lss \

FLASH_IMAGE += \
CARD_ECU.hex \

EEPROM_IMAGE += \
CARD_ECU.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: CARD_ECU.elf secondary-outputs

# Tool invocations
CARD_ECU.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,CARD_ECU.map -mmcu=atmega32 -o "CARD_ECU.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

CARD_ECU.lss: CARD_ECU.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S CARD_ECU.elf  >"CARD_ECU.lss"
	@echo 'Finished building: $@'
	@echo ' '

CARD_ECU.hex: CARD_ECU.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex CARD_ECU.elf  "CARD_ECU.hex"
	@echo 'Finished building: $@'
	@echo ' '

CARD_ECU.eep: CARD_ECU.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex CARD_ECU.elf  "CARD_ECU.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: CARD_ECU.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t CARD_ECU.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) CARD_ECU.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
