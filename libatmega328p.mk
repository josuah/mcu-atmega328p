OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
CPP = avr-cpp
CC = avr-gcc -mmcu=atmega328p
AR = avr-ar
GDB = avr-gdb
AVRDUDE = avrdude -p atmega328p -c arduino -b 115200 -P /dev/ttyU0

flash: firmware.hex
	${AVRDUDE} -qu -U flash:w:firmware.hex

.SUFFIXES: .c .s .S .o .elf .asm .hex
.S.o:

firmware.elf: ${OBJ}
	${CC} ${LDFLAGS} -Wl,-Map=firmware.map -Wl,-Tlibatmega328p.ld -Wl,--gc-sections -static -nostdlib -o $@ ${OBJ} ${LIBS}

.c.o:
	${CC} ${CFLAGS} -ffunction-sections -fdata-sections -fno-jump-tables -c -o $@ $<

.S.o:
	${CC} ${CFLAGS} -D__ASSEMBLY__ -c -o $@ $<

.elf.asm:
	${OBJDUMP} -z -d $< >$@

.elf.hex:
	${OBJCOPY} -j .text -j .data -O ihex $< $@
