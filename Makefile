CFLAGS = -Wall -Wextra -std=c99 -pedantic
OBJ = firmware.o libatmega328p.o libatmega328p.asm.o libc.o

all: firmware.elf firmware.asm

clean:
	rm -f *.[os] ${SDK}/*.[os] *.asm *.elf *.map *.hex
ocd:
	${OPENOCD}
gdb:
	${GDB} -x ${SDK}/script.gdb

include libatmega328p.mk
