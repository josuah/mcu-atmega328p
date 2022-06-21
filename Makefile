CFLAGS = -Wall -Wextra -std=c99 -pedantic -ggdb
OBJ = libatmega328p.o libc.o \
	example.o

all: firmware.elf firmware.asm

clean:
	rm -f *.[os] ${SDK}/*.[os] *.asm *.elf *.map *.hex *.bin *.uf2

ocd:
	${OPENOCD}

gdb:
	${GDB} -x ${SDK}/script.gdb


include libatmega328p.mk
