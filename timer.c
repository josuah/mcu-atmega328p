#include "binary.h"
#include "registers.h"
#include "functions.h"

enum config {
	/* how many bits is the internal timer register? */
	REG_LEN = 8,

	/* responsible of accuracy, but should be long enough for any interrupt */
	PRESCALER = 64, CLOCK_SOURCE = CSx64,
};

static struct {
	volatile uint64_t timer0_ovf, timer1_ovf, timer2_ovf;
} ctx;

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
		runtime_assert(!"wrong WGM0 mode");
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
		runtime_assert(!"wrong WGM1 mode");
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
		runtime_assert(!"wrong WGM2 mode");
	}
	TCCR2A = WGM2A(mode) | COM1A(out);
	TCCR2B = WGM2B(mode) | CS2(cs);
}

uint64_t
timer_gettime(void)
{
	uint64_t ovf;

	cli();
	ovf = ctx.timer0_ovf;
	sei();

	/* uptime = ovf * (1<<REG_LEN) * prescaler / freqcpu */
	return ovf * (1ull<<REG_LEN) * PRESCALER / (CPU_FREQ / 1000000UL);
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
	ctx.timer0_ovf++;
}

void
interrupt_timer1_ovf(void)
{
	ctx.timer1_ovf++;
}

void
interrupt_timer2_ovf(void)
{
	ctx.timer2_ovf++;
}
