################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SERVICE/UI/subdir.mk
-include SERVICE/DRIVE/subdir.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/PWM/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/DELAY/subdir.mk
-include ECUAL/MOTOR/subdir.mk
-include ECUAL/LED/subdir.mk
-include ECUAL/KEYPAD/subdir.mk
-include ECUAL/BTN/subdir.mk
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
BuildYourCarV1.lss \

FLASH_IMAGE += \
BuildYourCarV1.hex \

EEPROM_IMAGE += \
BuildYourCarV1.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: BuildYourCarV1.elf secondary-outputs

# Tool invocations
BuildYourCarV1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,BuildYourCarV1.map -mmcu=atmega32 -o "BuildYourCarV1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

BuildYourCarV1.lss: BuildYourCarV1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S BuildYourCarV1.elf  >"BuildYourCarV1.lss"
	@echo 'Finished building: $@'
	@echo ' '

BuildYourCarV1.hex: BuildYourCarV1.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex BuildYourCarV1.elf  "BuildYourCarV1.hex"
	@echo 'Finished building: $@'
	@echo ' '

BuildYourCarV1.eep: BuildYourCarV1.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex BuildYourCarV1.elf  "BuildYourCarV1.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: BuildYourCarV1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 BuildYourCarV1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) BuildYourCarV1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
