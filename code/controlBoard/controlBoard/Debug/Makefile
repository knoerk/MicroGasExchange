################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../include


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ADC.c \
../atm_programs.c \
../calculate_means.c \
../can.c \
../comm.c \
../controlBoard.c \
../debug.c \
../simple_delay.c \
../eepromValues.c \
../eeprom_functions.c \
../I2C.c \
../init.c \
../Interrupts.c \
../recieve_command.c \
../regelung.c \
../sensValues.c \
../SPI.c \
../uart.c \
../_StackInstrument.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC.o \
atm_programs.o \
calculate_means.o \
can.o \
comm.o \
controlBoard.o \
debug.o \
simple_delay.o \
eepromValues.o \
eeprom_functions.o \
I2C.o \
init.o \
Interrupts.o \
recieve_command.o \
regelung.o \
sensValues.o \
SPI.o \
uart.o \
_StackInstrument.o

OBJS_AS_ARGS +=  \
ADC.o \
atm_programs.o \
calculate_means.o \
can.o \
comm.o \
controlBoard.o \
debug.o \
simple_delay.o \
eepromValues.o \
eeprom_functions.o \
I2C.o \
init.o \
Interrupts.o \
recieve_command.o \
regelung.o \
sensValues.o \
SPI.o \
uart.o \
_StackInstrument.o

C_DEPS +=  \
ADC.d \
atm_programs.d \
calculate_means.d \
can.d \
comm.d \
controlBoard.d \
debug.d \
simple_delay.d \
eepromValues.d \
eeprom_functions.d \
I2C.d \
init.d \
Interrupts.d \
recieve_command.d \
regelung.d \
sensValues.d \
SPI.d \
uart.d \
_StackInstrument.d

C_DEPS_AS_ARGS +=  \
ADC.d \
atm_programs.d \
calculate_means.d \
can.d \
comm.d \
controlBoard.d \
debug.d \
simple_delay.d \
eepromValues.d \
eeprom_functions.d \
I2C.d \
init.d \
Interrupts.d \
recieve_command.d \
regelung.d \
sensValues.d \
SPI.d \
uart.d \
_StackInstrument.d

OUTPUT_FILE_PATH +=controlBoard.elf

OUTPUT_FILE_PATH_AS_ARGS +=controlBoard.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler







































./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 3.4.2
	$(QUOTE)C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -DDEBUG -DF_CPU=8000000UL  -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32 -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 3.4.2
	$(QUOTE)C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="controlBoard.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega32 
	@echo Finished building target: $@
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "controlBoard.elf" "controlBoard.hex"
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "controlBoard.elf" "controlBoard.eep" || exit 0
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "controlBoard.elf" > "controlBoard.lss"
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "controlBoard.elf" "controlBoard.srec"
	"C:\Programme\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.2.939\avr8-gnu-toolchain\bin\avr-size.exe" "controlBoard.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "controlBoard.elf" "controlBoard.a" "controlBoard.hex" "controlBoard.lss" "controlBoard.eep" "controlBoard.map" "controlBoard.srec"
	