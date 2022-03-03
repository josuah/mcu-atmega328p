# thank you N. for the first stone

MCU = atmega328p

BIN= blinky-asm
OBJ= ${BIN:=.o}

CC= avr-gcc
AVRDUDE= avrdude -p ${MCU} -c arduino -P /dev/ttyU0 -b 115200
OBJCOPY= avr-objcopy
OBJDUMP= avr-objdump
CFLAGS= -g -Wall -O0 -mmcu=${MCU}
LDFLAGS= -Wl,-Map,${BIN}.map

all: ${BIN}.elf ${BIN}.asm

${BIN}.elf: ${OBJ}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${OBJ}

.SUFFIXES: .elf .hex .asm

.elf.hex:
	${OBJCOPY} -j .text -j .data -O ihex $< $@

.elf.asm:
	${OBJDUMP} -z -j .text -m avr5 -d $< >$@

clean:
	rm -rf *.o *.elf *.asm *.hex *.lst *.map *.out

reset:
	${AVRDUDE}

flash: ${BIN}.hex
	${AVRDUDE} -D -u -U flash:w:${BIN}.hex
