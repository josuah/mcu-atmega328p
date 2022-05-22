CFLAGS = -Wall -Wextra -std=c99 -pedantic -ggdb
OBJ = example.o
SDK = .
include ${SDK}/script.mk
flash: flash.avrdude
