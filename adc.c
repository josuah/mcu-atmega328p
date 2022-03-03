#include "binary.h"
#include "registers.h"
#include "functions.h"

struct {
	uint16_t value;
	uint16_t volatile status;
} ctx;

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
	ctx.status = 1;

        /* trigger an ADC conversion on portA pin7 with internal
         * reference voltage and a left-adjusted number */
	ADMUX = MUX(admux) | REFS(ref) | 0*ADLAR;
	ADCSRA |= 1*ADSC;

	while (ctx.status == 1);
	return ctx.value;
}

void
interrupt_adc(void)
{
	ctx.value = *ADC;
	ctx.status = 0;
}
