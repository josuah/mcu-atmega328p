OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CPP = avr-cpp
CC = avr-gcc -mmcu=atmega328p
AS = avr-as -mmcu=atmega328p
LD = avr-ld
AR = avr-ar
GDB = avr-gdb
AVRDUDE = avrdude -p atmega328p -c arduino -b 115200
SDK_OBJ = ${SDK}/init.o ${SDK}/gpio.o ${SDK}/i2c.o ${SDK}/timer.o \
	${SDK}/uart.o ${SDK}/assert.o
