#include <zmcu.atmega328p.h>

/*
 * I²C is named Two Wires Interface by Atmel/Microchip
 * idea from https://github.com/scttnlsn/avr-i2c/blob/master/ctx.c
 */

enum {
	START_OK = 0x08,
	REP_START_OK = 0x10,
	WR_SLA_ACK = 0x18,
	WR_SLA_NACK = 0x20,
	WR_DATA_ACK = 0x28,
	WR_DATA_NACK = 0x30,
	RD_SLA_ACK = 0x40,
	RD_SLA_NACK = 0x48,
	RD_DATA_ACK = 0x50,
	RD_DATA_NACK = 0x58,
	ARB_LOST = 0x38,

};

#define kHz	1000

#define	STOP	(TWINT | TWSTO)
#define	CONT	(TWINT | TWEN | TWIE)
#define	START	(CONT | TWSTA)
#define	ACK	(CONT | TWEA)
#define	NACK	(CONT)

#ifndef I2C_SCL_FREQ
#define I2C_SCL_FREQ	(10*kHz)
#endif

struct {
	uint8_t addr;
	uint8_t *buf;
	size_t sz, i;
	volatile int status;
} ctx;

void
i2c_init(void)
{
	uint8_t map[] = { 1, 4, 16, 64 }, presc;

	/* disable power reduction for TWI */
	PRR &= ~PRTWI;

	/* I2C_SCL_FREQ = CPU_FREQ / (16 + 2 * TWBR * presc) */
	presc = map[TWSR & TWPS(3)];
	TWBR = (CPU_FREQ / I2C_SCL_FREQ - 16) / (2 * presc);

	/* setup an internal pull-up resistor on the bus */
	PORTC |= 1<<4 | 1<<5;
}

static void
i2c_start(void)
{
	TWCR = START;
}

int
i2c_read(uint8_t addr, uint8_t *buf, size_t sz)
{
	ctx.addr = addr << 1 | 1;
	ctx.buf = buf;
	ctx.sz = sz;
	ctx.i = 0;
	ctx.status = 1;

	i2c_start();
	while (ctx.status == 1);
	runtime_assert(ctx.status == -1 || ctx.i == ctx.sz);
	return ctx.status;
}

int
i2c_write(uint8_t addr, uint8_t const *buf, size_t sz)
{
	ctx.addr = addr << 1 | 0;
	ctx.buf = (uint8_t *)buf;
	ctx.sz = sz;
	ctx.i = 0;
	ctx.status = 1;

	i2c_start();
	while (ctx.status == 1);
	runtime_assert(ctx.status == -1 || ctx.i == ctx.sz);
	return ctx.status;
}

int
i2c_scan(uint8_t *addr)
{
	while (++*addr < 128)
		if (i2c_write(*addr, NULL, 0) == 0)
			return 1;
	return 0;
}

void
interrupt_twi(void)
{
	switch (TWSR & B11111000) {
	case START_OK:
	case REP_START_OK:
		TWDR = ctx.addr;
		TWCR = CONT;
		break;
	case ARB_LOST:
		ctx.status = -1;
		break;
	case WR_SLA_ACK:
	case WR_DATA_ACK:
		if (ctx.i < ctx.sz) {
			TWDR = ctx.buf[ctx.i++];
			TWCR = CONT;
		}else{
			TWCR = STOP;
			ctx.status = 0;
		}
		break;
	case WR_SLA_NACK:
	case WR_DATA_NACK:
		TWCR = STOP;
		ctx.status = -1;
		break;
	case RD_SLA_ACK:
		TWCR = (ctx.i + 1 < ctx.sz) ? ACK : NACK;
		break;
	case RD_SLA_NACK:
		TWCR = STOP;
		ctx.status = -1;
		break;
	case RD_DATA_ACK:
		ctx.buf[ctx.i++] = TWDR;
		TWCR = (ctx.i + 1 < ctx.sz) ? ACK : NACK;
		break;
	case RD_DATA_NACK:
		ctx.buf[ctx.i++] = TWDR;
		TWCR = STOP;
		ctx.status = 0;
		break;
	}
}
