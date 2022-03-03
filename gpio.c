#include "binary.h"
#include "registers.h"
#include "functions.h"

void
gpio_init(void)
{
	/* set direction of pin5 to "out" */
	DDRB |= 1<<5;
}

void
gpio_set(uint8_t *port, uint8_t mask)
{
	*port |= mask;
}

void
gpio_clr(uint8_t *port, uint8_t mask)
{
	*port &= ~mask;
}

void
gpio_led(int on)
{
	PORTB = (on) ? (PORTB | 1<<5) : (PORTB & ~(1<<5));
}
