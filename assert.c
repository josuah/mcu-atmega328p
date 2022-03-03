#include "binary.h"
#include "registers.h"
#include "functions.h"

void
runtime_assert(int expr)
{
	if (expr)
		return;

	for (;;) {
		for (volatile uint64_t i = 0; i < 3000; i++);
		gpio_led(1);
		for (volatile uint64_t i = 0; i < 3000; i++);
		gpio_led(0);
	}
}
