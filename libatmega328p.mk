OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CPP = avr-cpp -D__AVR_ATmega328P__
CC = avr-gcc -mmcu=atmega328p
LD = avr-ld -L/usr/local/avr/lib/avr5
AR = avr-ar
GDB = avr-gdb
AVRDUDE = avrdude -p atmega328p -c arduino -b 115200 -P ${AVRDUDE_PORT}
AVRDUDE_PORT = /dev/ttyU0

flash: firmware.hex
	${AVRDUDE} -qu -U flash:w:firmware.hex

.SUFFIXES: .c .s .S .o .elf .asm .hex
.S.o:

firmware.elf: ${OBJ}
	${LD} ${LDFLAGS} -Map=firmware.map -Tlibatmega328p.ld --gc-sections -static -no-stdlibs -o $@ ${OBJ}

.c.o:
	${CC} ${CPPFLAGS} -ffunction-sections -fdata-sections ${CFLAGS} -c -o $@ $<

.S.o:
	${CC} ${CPPFLAGS} ${CFLAGS} -c -o $@ $<

.elf.asm:
	${OBJDUMP} -z -d $< >$@

.elf.hex:
	${OBJCOPY} -j .text -j .data -O ihex $< $@
