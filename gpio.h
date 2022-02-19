#include <stddef.h>
#include <stdint.h>

/* port B input */
#define PINB		(*(uint8_t volatile *)0x23)

/* port B data direction register */
#define DDRB		(*(uint8_t volatile *)0x24)

/* port B output */
#define PORTB		(*(uint8_t volatile *)0x25)

/* port C input */
#define PINC		(*(uint8_t volatile *)0x26)

/* port C data direction register */
#define DDRC		(*(uint8_t volatile *)0x27)

/* port C output */
#define PORTC		(*(uint8_t volatile *)0x28)

/* port D input */
#define PIND		(*(uint8_t volatile *)0x29)

/* port D data direction register */
#define DDRD		(*(uint8_t volatile *)0x2A)

/* port D output */
#define PORTD		(*(uint8_t volatile *)0x2B)

/* setup GPIO (builtin led mostly) */
void gpio_init(void);

/* enable or disable the builtin led */
void gpio_led(int onoff);

/* set pin up for all bits up in mask */
void gpio_set(uint8_t *port, uint8_t mask);

/* set pin down for all bits up in mask */
void gpio_clr(uint8_t *port, uint8_t mask);
