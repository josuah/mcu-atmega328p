#include "libc.h"
#include "libatmega328p.h"


/// INIT ///


extern int main(void);
extern char __data_start, __data_end, __data_load_start;
extern char __bss_start, __bss_end, __stack_top;

void
__reset_handler(void)
{
	volatile char *dst, *src = &__data_load_start;

	for (dst = &__data_start; dst < &__data_end; *dst++ = *src++);
	for (dst = &__bss_start; dst < &__bss_end; *dst++ = 0);
	main();
	for (int volatile i = 0 ;; i++);
}

/* so that the debugger can immediately see which fault was triggered */
void __null_handler(void)               { for (int volatile i = 0;; i++); }


/// ADC ///


#if 0

static uint16_t adc_value;
static uint16_t volatile adc_status;

void
adc_init(uint8_t ps)
{
	/* enable ADC module and its interrupt */
	PRR &= ~(PRADC);
	ADCSRA = 1*ADEN | 0*ADSC | 0*ADATE | 0*ADIF | 1*ADIE | ADPS(ps);
}

uint16_t
adc_read(uint8_t admux, uint8_t ref)
{
	adc_status = 1;

        /* trigger an ADC conversion on portA pin7 with internal
         * reference voltage and a left-adjusted number */
	ADMUX = MUX(admux) | REFS(ref) | 0*ADLAR;
	ADCSRA |= 1*ADSC;

	while (adc_status == 1);
	return adc_value;
}

void
interrupt_adc(void)
{
	adc_value = *ADC;
	adc_status = 0;
}

#endif


/// GPIO ///


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


/// I2C ///


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

static uint8_t i2c_addr;
static uint8_t *i2c_buf;
static size_t i2c_sz, i2c_i;
static volatile int i2c_status;

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
	i2c_addr = addr << 1 | 1;
	i2c_buf = buf;
	i2c_sz = sz;
	i2c_i = 0;
	i2c_status = 1;

	i2c_start();
	while (i2c_status == 1);
	assert(i2c_status == -1 || i2c_i == i2c_sz);
	return i2c_status;
}

int
i2c_write(uint8_t addr, uint8_t const *buf, size_t sz)
{
	i2c_addr = addr << 1 | 0;
	i2c_buf = (uint8_t *)buf;
	i2c_sz = sz;
	i2c_i = 0;
	i2c_status = 1;

	i2c_start();
	while (i2c_status == 1);
	assert(i2c_status == -1 || i2c_i == i2c_sz);
	return i2c_status;
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
	switch (TWSR & 0xF8) {
	case START_OK:
	case REP_START_OK:
		TWDR = i2c_addr;
		TWCR = CONT;
		break;
	case ARB_LOST:
		i2c_status = -1;
		break;
	case WR_SLA_ACK:
	case WR_DATA_ACK:
		if (i2c_i < i2c_sz) {
			TWDR = i2c_buf[i2c_i++];
			TWCR = CONT;
		}else{
			TWCR = STOP;
			i2c_status = 0;
		}
		break;
	case WR_SLA_NACK:
	case WR_DATA_NACK:
		TWCR = STOP;
		i2c_status = -1;
		break;
	case RD_SLA_ACK:
		TWCR = (i2c_i + 1 < i2c_sz) ? ACK : NACK;
		break;
	case RD_SLA_NACK:
		TWCR = STOP;
		i2c_status = -1;
		break;
	case RD_DATA_ACK:
		i2c_buf[i2c_i++] = TWDR;
		TWCR = (i2c_i + 1 < i2c_sz) ? ACK : NACK;
		break;
	case RD_DATA_NACK:
		i2c_buf[i2c_i++] = TWDR;
		TWCR = STOP;
		i2c_status = 0;
		break;
	}
}


/// TIMER ///


/* how many bits is the internal timer register? */
#define TIMER_REG_LEN	(1ull << 8)

/* responsible of accuracy, but should be long enough for any interrupt */
#define TIMER_PRESCALER	64

static volatile uint64_t timer0_ovf, timer1_ovf, timer2_ovf;

/* CPU_FREQ / 1000000UL used in timer_gettime() */
//STATIC_ASSERT(CPU_FREQ % 1000000UL == 0);

void
timer0_init(int cs, int mode)
{
	int out = 0;

	switch (mode) {
	case WGM0_NORMAL_0xFF:
	case WGM0_FAST_0xFF:
	case WGM0_PHASE_CORRECT_0xFF:
		out = COM_PULSE;
		break;
	case WGM0_CTC_OCRA:
	case WGM0_FAST_OCRA:
	case WGM0_PHASE_CORRECT_OCRA:
		out = COM_TOGGLE;
		break;
	default:
		assert(!"wrong WGM0 mode");
	}
	TCCR0A = WGM0A(mode) | COM1A(out);
	TCCR0B = WGM0B(mode) | CS0(cs);
	TIMSK0 |= TOIE0;
}

void
timer1_init(int cs, int mode)
{
	int out = 0;

	switch (mode) {
	case WGM1_NORMAL_0xFFFF:
	case WGM1_FAST_0x00FF:
	case WGM1_FAST_0x01FF:
	case WGM1_FAST_0x03FF:
	case WGM1_PHASE_CORRECT_0x01FF:
	case WGM1_PHASE_CORRECT_0x03FF:
		out = COM_TOGGLE;
		break;
	case WGM1_CTC_ICR1:
	case WGM1_CTC_OCRA:
	case WGM1_FAST_ICR1:
	case WGM1_FAST_OCRA:
	case WGM1_PHASE_CORRECT_0x00FF:
	case WGM1_PHASE_CORRECT_ICR1:
	case WGM1_PHASE_CORRECT_OCRA:
	case WGM1_PHASE_FREQ_CORRECT_ICR1:
	case WGM1_PHASE_FREQ_CORRECT_OCRA:
		out = COM_PULSE;
		break;
	default:
		assert(!"wrong WGM1 mode");
	}
	TCCR1A = WGM1A(mode) | COM1A(out);
	TCCR1B = WGM1B(mode) | CS1(cs);
}

void
timer2_init(int cs, int mode)
{
	int out = 0;

	switch (mode) {
	case WGM2_NORMAL_0xFF:
	case WGM2_FAST_0xFF:
	case WGM2_PHASE_CORRECT_0xFF:
		out = COM_PULSE;
		break;
	case WGM2_CTC_OCR0A:
	case WGM2_FAST_OCRA:
	case WGM2_PHASE_CORRECT_OCR0A:
		out = COM_TOGGLE;
		break;
	default:
		assert(!"wrong WGM2 mode");
	}
	TCCR2A = WGM2A(mode) | COM1A(out);
	TCCR2B = WGM2B(mode) | CS2(cs);
}

uint64_t
timer_gettime(void)
{
	uint64_t ovf;

	cli();
	ovf = timer0_ovf;
	sei();

	/* uptime = ovf * TIMER_REG_LEN * prescaler / freqcpu */
	return ovf * TIMER_REG_LEN * TIMER_PRESCALER / (CPU_FREQ / 1000000UL);
}

void
timer_sleep(uint64_t us)
{
	us += timer_gettime();
	while (timer_gettime() < us);
}

void
interrupt_timer0_ovf(void)
{
	timer0_ovf++;
}

void
interrupt_timer1_ovf(void)
{
	timer1_ovf++;
}

void
interrupt_timer2_ovf(void)
{
	timer2_ovf++;
}


/// UART ///


enum {
	OFF = 0, ON = 1,
};

#ifndef USART_BAUDRATE
#define USART_BAUDRATE 9600
#endif

static uint8_t const *uart_buf;
static size_t uart_sz, uart_i;
static volatile int uart_status;

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
	uart_status = 1;
	uart_buf = buf;
	uart_sz = sz;
	uart_i = 0;

	set_interrupt(ON);
	while (uart_status == 1);
	return uart_status;
}

void
interrupt_usart_udre(void)
{
	if (uart_i == uart_sz) {
		uart_status = 0;
		set_interrupt(OFF);
		return;
	}
	/* fill the data register which queue the write in hardware */
	UDR0 = uart_buf[uart_i++];
}
