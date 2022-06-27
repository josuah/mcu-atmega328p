OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CPP = avr-cpp
CC = avr-gcc -mmcu=atmega328p
LD = avr-ld
AR = avr-ar
GDB = avr-gdb
AVRDUDE = avrdude -p atmega328p -c arduino -b 115200 -P ${AVRDUDE_PORT}
AVRDUDE_PORT = /dev/ttyU0

flash: firmware.hex
	${AVRDUDE} -qu -U flash:w:firmware.hex

.SUFFIXES: .c .s .S .o .elf .asm .hex
.S.o:

firmware.elf: ${OBJ}
	${LD} ${LDFLAGS} -Map=firmware.map -Tlibatmega328p.ld --gc-sections -static -nostdlib -o $@ ${OBJ}

.c.o:
	${CC} ${CFLAGS} -ffunction-sections -fdata-sections -c -o $@ $<

.S.o:
	${CC} ${CFLAGS} -D__ASSEMBLY__ -c -o $@ $<

.elf.asm:
	${OBJDUMP} -z -d $< >$@

.elf.hex:
	${OBJCOPY} -j .text -j .data -O ihex $< $@
