OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CPP = avr-cpp -D__AVR_ATmega328P__
CC = avr-gcc -mmcu=atmega328p
AS = avr-as -mmcu=atmega328p
LD = avr-ld -L/usr/local/avr/lib/avr5
AR = avr-ar
GDB = avr-gdb
AVRDUDE = avrdude -p atmega328p -c arduino -b 115200 -P ${AVRDUDE_PORT}
AVRDUDE_PORT = /dev/ttyU0

SDK_OBJ = ${SDK}/init.o ${SDK}/gpio.o ${SDK}/i2c.o ${SDK}/timer.o \
	${SDK}/uart.o ${SDK}/asm.o

all: firmware.elf firmware.asm

clean:
	rm -f *.[os] ${SDK}/*.[os] *.asm *.elf *.map *.hex *.bin *.uf2

ocd:
	${OPENOCD}

gdb:
	${GDB} -x ${SDK}/script.gdb

flash: firmware.hex
	${AVRDUDE} -qu -U flash:w:firmware.hex

.SUFFIXES: .c .s .S .o .elf .bin .asm .hex .uf2
.S.o:

firmware.elf: ${SDK_OBJ} ${OBJ}
	${LD} ${LDFLAGS} -Map=firmware.map --gc-sections -T${SDK}/script.ld -nostdlib -static -o $@ ${SDK_OBJ} ${OBJ}

.c.o:
	${CC} ${CPPFLAGS} -I${SDK} ${CFLAGS} -ffunction-sections -fdata-sections -c -o $@ $<

.S.s:
	${CPP} ${CPPFLAGS} -I${SDK} -o $@ $<

.s.o:
	${AS} ${CPPFLAGS} -I${SDK} ${ASFLAGS} -c -o $@ $<

.elf.asm:
	${OBJDUMP} -z -d $< >$@

.elf.hex:
	${OBJCOPY} -j .text -j .data -O ihex $< $@