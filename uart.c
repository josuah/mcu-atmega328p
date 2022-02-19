#include <zmcu.atmega328p.h>

enum {
	OFF = 0, ON = 1,
};

#ifndef USART_BAUDRATE
#define USART_BAUDRATE 9600
#endif

static struct {
	uint8_t const *buf;
	size_t sz, i;
	volatile int status;
} ctx;

static void
set_interrupt(int onoff)
{
	/* Usart Data Register empty Interrupt Enable (ON/OFF) */
	UCSR0B = (onoff) ? (UCSR0B | UDRIE0) : (UCSR0B & ~UDRIE0);
}

void
uart_init(void)
{
	/* disable power reduction for USART */
	PRR &= ~PRUSAR0;

	/* enable RX and TX circuits and interrupts */
	UCSR0B = RXEN0 | TXEN0;

	/* set frame format: 8data 1stop 0parity */
	UCSR0C = UCSZ0C(3);

	/* set the baud rate after enabling the transmitter */
	UBRR0 = CPU_FREQ / 16 / USART_BAUDRATE - 1;
}

uint8_t
uart_recv(void)
{
	/* wait that a byte was received */
	while (!(UCSR0A & RXC0));

	/* return the data register now that it contains input */
	return UDR0;
}

int
uart_write(uint8_t const *buf, size_t sz)
{
	ctx.status = 1;
	ctx.buf = buf;
	ctx.sz = sz;
	ctx.i = 0;

	set_interrupt(ON);
	while (ctx.status == 1);
	return ctx.status;
}

void
interrupt_usart_udre(void)
{
	if (ctx.i == ctx.sz) {
		ctx.status = 0;
		set_interrupt(OFF);
		return;
	}
	/* fill the data register which queue the write in hardware */
	UDR0 = ctx.buf[ctx.i++];
}
