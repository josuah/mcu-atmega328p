#include "libc.h"
#include "libatmega328p.h"

int
main(void)
{
	i2c_init();
	sei();

	for (;;) i2c_write(0x33, (uint8_t *)"123", 3);

	return 0;
}
