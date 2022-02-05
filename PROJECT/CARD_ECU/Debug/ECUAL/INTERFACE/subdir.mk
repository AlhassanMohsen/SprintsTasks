################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/INTERFACE/INTERFACE_SLAVE.c \
../ECUAL/INTERFACE/TERMINAL_SLAVE.c 

OBJS += \
./ECUAL/INTERFACE/INTERFACE_SLAVE.o \
./ECUAL/INTERFACE/TERMINAL_SLAVE.o 

C_DEPS += \
./ECUAL/INTERFACE/INTERFACE_SLAVE.d \
./ECUAL/INTERFACE/TERMINAL_SLAVE.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/INTERFACE/%.o: ../ECUAL/INTERFACE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


