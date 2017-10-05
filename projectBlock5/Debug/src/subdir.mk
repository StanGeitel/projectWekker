################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/GPIO.c \
../src/I2C.c \
../src/IR.c \
../src/RIT.c \
../src/RealTimeClock.c \
../src/SPI.c \
../src/alarm.c \
../src/calculator.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/display.c \
../src/font5x7.c \
../src/projectBlock5.c \
../src/sound.c \
../src/timer.c 

OBJS += \
./src/GPIO.o \
./src/I2C.o \
./src/IR.o \
./src/RIT.o \
./src/RealTimeClock.o \
./src/SPI.o \
./src/alarm.o \
./src/calculator.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/display.o \
./src/font5x7.o \
./src/projectBlock5.o \
./src/sound.o \
./src/timer.o 

C_DEPS += \
./src/GPIO.d \
./src/I2C.d \
./src/IR.d \
./src/RIT.d \
./src/RealTimeClock.d \
./src/SPI.d \
./src/alarm.d \
./src/calculator.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/display.d \
./src/font5x7.d \
./src/projectBlock5.d \
./src/sound.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


