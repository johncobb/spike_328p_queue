################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include util/subdir.mk
-include queue/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
spike_328p_queue.lss \

FLASH_IMAGE += \
spike_328p_queue.hex \

EEPROM_IMAGE += \
spike_328p_queue.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: spike_328p_queue.elf secondary-outputs

# Tool invocations
spike_328p_queue.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,spike_328p_queue.map -mmcu=atmega328p -o "spike_328p_queue.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

spike_328p_queue.lss: spike_328p_queue.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S spike_328p_queue.elf  >"spike_328p_queue.lss"
	@echo 'Finished building: $@'
	@echo ' '

spike_328p_queue.hex: spike_328p_queue.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex spike_328p_queue.elf  "spike_328p_queue.hex"
	@echo 'Finished building: $@'
	@echo ' '

spike_328p_queue.eep: spike_328p_queue.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex spike_328p_queue.elf  "spike_328p_queue.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: spike_328p_queue.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega328p spike_328p_queue.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) spike_328p_queue.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
