CFLAGS = -Wall -Wextra -std=c99 -pedantic -ggdb
OBJ = example.o
SDK = .
include ${SDK}/Makefile.inc
flash: flash
