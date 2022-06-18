OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CPP = avr-cpp -D__AVR_ATmega328P__
CC = avr-gcc -mmcu=atmega328p
AS = avr-as -mmcu=atmega328p
LD = avr-ld -L/usr/local/avr/lib/avr5
AR = avr-ar
GDB = avr-gdb
AVRDUDE = avrdude -p atmega328p -c arduino -b 115200
SDK_OBJ = ${SDK}/init.o ${SDK}/gpio.o ${SDK}/i2c.o ${SDK}/timer.o \
	${SDK}/uart.o ${SDK}/asm.o
