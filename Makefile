AVRDUDE = avrdude -p atmega328p -c arduino -b 115200 -P /dev/ttyU0
CC = avr-gcc -mmcu=atmega328p
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump

CFLAGS += -Wall -Wextra -Wconversion -Wmissing-prototypes -Wno-array-bounds
CFLAGS += -std=c99 -pedantic
CFLAGS += -Os
CFLAGS += -DNDEBUG

OBJ += libatmega328p.o 
OBJ += libatmega328p.asm.o 
OBJ += firmware.o
LIBS += -lgcc -lc

all: firmware.hex

clean:
	rm -f *.[os] *.asm *.elf *.map *.hex

flash: firmware.hex
	${AVRDUDE} -qu -U flash:w:firmware.hex

firmware.elf: ${OBJ}
	${CC} ${LDFLAGS} -Wl,-Map=firmware.map -Wl,-Tlibatmega328p.ld -Wl,--gc-sections -static -nostdlib -o $@ ${OBJ} ${LIBS}
	${OBJDUMP} -z -d $@ >$*.asm

$(OBJ): Makefile *.h

.SUFFIXES: .c .s .S .o .elf .asm .hex

.c.o:
	${CC} ${CFLAGS} -ffunction-sections -fdata-sections -fno-jump-tables -c -o $@ $<

.S.o:
	${CC} ${CFLAGS} -D__ASSEMBLY__ -c -o $@ $<

.elf.hex:
	${OBJCOPY} -j .text -j .data -O ihex $< $@
