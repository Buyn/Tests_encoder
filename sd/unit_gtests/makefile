################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries\gtest\subdir.mk
-include core\core\avr\subdir.mk
-include core\core\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
D:\Development\Ardunio\Eclipse\Home\sloeber-workspace\sd\unit_gtests\arduino.ar \

ELF += \
sd.elf \

HEX += \
sd.hex \


# All Target
all: sd

# Tool invocations
sd: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	${JANTJE.SIZE.SWITCH}
	@echo 'Finished building target: $@'
	@echo ' '

D:\Development\Ardunio\Eclipse\Home\sloeber-workspace\sd\unit_gtests\arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"D:\sloeber\arduinoPlugin\packages\Jantje\tools\MinGW\5.3.0/bin/ar" rcs     D:/Development/Ardunio/Eclipse/Home/sloeber-workspace/sd/unit_gtests/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

sd.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"D:\sloeber\arduinoPlugin\packages\Jantje\tools\MinGW\5.3.0/bin/g++" -w -Os  -Wl,--gc-sections  -o "D:/Development/Ardunio/Eclipse/Home/sloeber-workspace/sd/unit_gtests/sd.exe"   $(LINK_OBJ)   D:/Development/Ardunio/Eclipse/Home/sloeber-workspace/sd/unit_gtests/arduino.ar  "-LD:/Development/Ardunio/Eclipse/Home/sloeber-workspace/sd/unit_gtests" -lm
	@echo 'Finished building: $@'
	@echo ' '

sd.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${JANTJE.OBJCOPY}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ..\makefile.targets
