#include <avr/io.h>

int
main(void)
{
	/* set direction of PIN5 to "out" */
	DDRB |= 1<<5;

	for (;;) {
		/* led toggle */
		PORTB &= ~(1<<5);
		for (uint32_t u=0; u<0x10000; u++);
	}

	return 0;
}
