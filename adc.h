#include <stddef.h>
#include <stdint.h>

/* ADC pin multiplexing control */
#define ADMUX		(*(uint8_t volatile *)0x7C)
#define REFS		(1 << 6)
#define ADLAR		(1 << 5)
#define MUX		(1 << 0)

/* ADC status register B */
#define ADCSRB		(*(uint8_t volatile *)0x7B)
#define ACME		(1 << 6)
#define ADTS		(1 << 0)

/* ADC status register A */
#define ADCSRA		(*(uint8_t volatile *)0x7A)
#define ADEN		(1 << 7)
#define ADSC		(1 << 6)
#define ADATE		(1 << 5)
#define ADIF		(1 << 4)
#define ADIE		(1 << 3)
#define ADPS		(1 << 0)

/* ADC prescaler (ADPS) values */
#define ADPSx1		0x0
#define ADPSx2		0x1
#define ADPSx4		0x2
#define ADPSx8		0x3
#define ADPSx16		0x4
#define ADPSx32		0x5
#define ADPSx64		0x6
#define ADPSx128	0x7

/* ADC data register */
#define ADC		(*(uint16_t *)0x78)
#define ADCL		(*(uint8_t volatile *)0x78)
#define ADCH		(*(uint8_t volatile *)0x79)
