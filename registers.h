
/* ADC */

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


/* FUSES */

/* usage:
 *	.global	.fuses
 *		__fuses:
 *	.byte	LFUSE(FON<<FLAG | ... | DERIVED_OPT | ...)
 *	.byte	HFUSE(FON<<FLAG | ... | DERIVED_OPT | ...)
 *	.byte	EFUSE(FON<<FLAG | ... | DERIVED_OPT | ...)
 *
 * parenthesis are the factory values. Fuses values are kept across
 * resets/reboots/powercycles. When using assembly (.byte), they are
 * to be listed the same order as below. */
#define FON		0
#define FOFF		1

/* Low Fuse Bits */
#define LFUSE(byte)	(byte)
#define CKDIV8		(1 << 7)
#define CKOUT		(1 << 6)
#define SUT1		(1 << 5)
#define SUT0		(1 << 4)
#define CKSEL3		(1 << 3)
#define CKSEL2		(1 << 2)
#define CKSEL1		(1 << 1)
#define CKSEL0		(1 << 0)
/* Table 8-8 Start-up Times for the Low-frequency Crystal Oscillator
 * Clock Selection */
#define SUT_BOD_ON	(0<<SUT1 | 0<<SUT0)
#define SUT_FAST	(0<<SUT1 | 1<<SUT0)
#define SUT_SLOW	(1<<SUT1 | 0<<SUT0)
/* Table 8-1 Device Clocking Options Select */
#define CKSEL_CRYSTAL_LOWPOW  (1<<CKSEL3 | 1<<CKSEL2 | 1<<CKSEL1 | 1<<CKSEL0)
#define CKSEL_CRYSTAL_FULLPOW (0<<CKSEL3 | 1<<CKSEL2 | 1<<CKSEL1 | 0<<CKSEL0)
#define CKSEL_CRYSTAL_LOWFREQ (0<<CKSEL3 | 1<<CKSEL2 | 0<<CKSEL1 | 1<<CKSEL0)
#define CKSEL_CERAMIC_128KHZ (0<<CKSEL3 | 0<<CKSEL2 | 1<<CKSEL1 | 1<<CKSEL0)
#define CKSEL_CERAMIC_CALIB (0<<CKSEL3 | 0<<CKSEL2 | 1<<CKSEL1 | 0<<CKSEL0)
#define CKSEL_EXTERNAL	(0<<CKSEL3 | 0<<CKSEL2 | 0<<CKSEL1 | 0<<CKSEL0)

/* High Fuse Bits */
#define HFUSE(byte)	(byte)
#define RSTDISBL	(1 << 7)
#define DWEN		(1 << 6)
#define SPIEN		(1 << 5)
#define WDTON		(1 << 4)
#define EESAVE		(1 << 3)
#define BOOTSZ1		(1 << 2)
#define BOOTSZ0		(1 << 1)
#define BOOTRST		(1 << 0)
/* Table 26-7 Boot Size Configuration, ATmega328P*/
#define BOOTSZ_256	(1*BOOTSZ1 | 1*BOOTSZ0)
#define BOOTSZ_512	(1*BOOTSZ1 | 0*BOOTSZ0)
#define BOOTSZ_1024	(0*BOOTSZ1 | 1*BOOTSZ0)
#define BOOTSZ_2048	(0*BOOTSZ1 | 0*BOOTSZ0)

/* Extended Fuse Bits */
#define EFUSE(byte)	((byte) | 0xF8)
#define BODLEVEL2	(1 << 2)
#define BODLEVEL1	(1 << 1)
#define BODLEVEL0	(1 << 0)
/* Table 28-5 Extended Fuse Byte for ATmega328P */
#define BODLEVEL_OFF	(1*BODLEVEL2 | 1*BODLEVEL1 | 1*BODLEVEL0)
#define BODLEVEL_3V3	(1*BODLEVEL2 | 0*BODLEVEL1 | 1*BODLEVEL0)
#define BODLEVEL_5V	(1*BODLEVEL2 | 0*BODLEVEL1 | 0*BODLEVEL0)


/* GPIO */

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


/* TWI/I2C */

/* two-wire control register */
#define TWCR		(*(uint8_t volatile *)0xBC)
#define TWINT		(1 << 7)
#define TWEA		(1 << 6)
#define TWSTA		(1 << 5)
#define TWSTO		(1 << 4)
#define TWWC		(1 << 3)
#define TWEN		(1 << 2)
#define TWIE		(1 << 0)	

/* two-wire data register */
#define TWDR		(*(uint8_t volatile *)0xBB)

/* two-wire status register */
#define TWSR		(*(uint8_t volatile *)0xB9)
#define TWS		B11111000
#define TWPS(x)		((x) << 0)

/* two-wire bit rate regsiter */
#define TWBR		(*(uint8_t volatile *)0xB8)


/* POWER */

/* power reduction register */
#define PRR		(*(uint8_t volatile *)0x64)
#define PRTWI		(1 << 7)
#define PRTIM2		(1 << 6)
#define PRTIM0		(1 << 5)
#define PRTIM1		(1 << 3)
#define PRSPI		(1 << 2)
#define PRUSAR0		(1 << 1)
#define PRADC		(1 << 0)


/* TIMER/COUNTER */

/* values for CS% */
#define CSx1		0x1
#define CSx8		0x2
#define CSx64		0x3
#define CSx256		0x4
#define CSx1024		0x5

/* timer/counter 0 control register A */
#define TCCR0A		(*(uint8_t volatile *)0x44)
#define COM0A		(1 << 6)
#define COM0B		(1 << 4)
#define WGM0A(n)	((n) & B00000011)

/* timer/counter 0 control register B */
#define TCCR0B		(*(uint8_t volatile *)0x45)
#define FOC0A		(1 << 7)
#define FOC0B		(1 << 6)
#define WGM0B(n)	(((n) & B00000100) << 1)
#define CS0(x)		((x) << 0)

/* timer/counter 0 interrupt mask register */
#define TIMSK0		(*(uint8_t volatile *)0x6E)
#define OCIE0B		(1 << 2)
#define OCIE0A		(1 << 1)
#define TOIE0		(1 << 0)

/* timer/counter 0 output compare register A and B */
#define OCR0B		(*(uint8_t volatile *)0x48)
#define OCR0A		(*(uint8_t volatile *)0x47)

/* values for WGM0 */
#define WGM0_NORMAL_0xFF 0
#define WGM0_CTC_OCRA	2
#define WGM0_FAST_0xFF	3
#define WGM0_FAST_OCRA	7
#define WGM0_PHASE_CORRECT_0xFF 1
#define WGM0_PHASE_CORRECT_OCRA 5

/* timer/counter 1 control register A */
#define TCCR1A		(*(uint8_t volatile *)0x80)
#define COM1A(x)	((x) << 6)
#define COM1B(x)	((x) << 4)
#define WGM1A(n)	((n) & B00000011)

/* timer/counter 1 control register B */
#define TCCR1B		(*(uint8_t volatile *)0x81)
#define ICNC1		(1 << 7)
#define ICES1		(1 << 6)
#define WGM1B(n)	(((n) & B00001100) << 1) 
#define CS1(x)		((x) << 0)

/* timer/counter 1 control register C */
#define TCCR1C		(*(uint8_t volatile *)0x82)
#define FOC1A		(1 << 7)
#define FOC1B		(1 << 6)

/* timer/counter 1 output compare register A and B */
#define OCR1A		(*(uint16_t *)0x88)
#define OCR1B		(*(uint16_t *)0x8A)

/* values for WGM1 */
#define WGM1_NORMAL_0xFFFF 0
#define WGM1_CTC_ICR1	12
#define WGM1_CTC_OCRA	4
#define WGM1_FAST_0x00FF 5
#define WGM1_FAST_0x01FF 6
#define WGM1_FAST_0x03FF 7
#define WGM1_FAST_ICR1	14
#define WGM1_FAST_OCRA	15
#define WGM1_PHASE_CORRECT_0x00FF 1
#define WGM1_PHASE_CORRECT_0x01FF 2
#define WGM1_PHASE_CORRECT_0x03FF 3
#define WGM1_PHASE_CORRECT_ICR1 10
#define WGM1_PHASE_CORRECT_OCRA 11
#define WGM1_PHASE_FREQ_CORRECT_ICR1 8
#define WGM1_PHASE_FREQ_CORRECT_OCRA 9

/* timer/counter 2 control register A */
#define TCCR2A		(*(uint8_t volatile *)0xB0)
#define COM2A		(1 << 6)
#define COM2B		(1 << 4)
#define WGM2A(n)	((n) & B00000011)

/* timer/counter 2 control register B */
#define TCCR2B		(*(uint8_t volatile *)0xB1)
#define FOC2A		(1 << 7)
#define FOC2B		(1 << 6)
#define WGM2B(n)	((n) & B00001000) 
#define CS2(x)		((x) << 0)

/* timer/counter 2 counter value */
#define TCNT2		(*(uint8_t volatile *)0xB2)

/* timer/counter 2 output compare register A and B */
#define OCR2B		(*(uint8_t volatile *)0xB4)
#define OCR2A		(*(uint8_t volatile *)0xB3)

/* values for WGM2 */
#define WGM2_NORMAL_0xFF 0
#define WGM2_CTC_OCR0A	2
#define WGM2_FAST_0xFF	3
#define WGM2_FAST_OCRA	7
#define WGM2_PHASE_CORRECT_0xFF 1
#define WGM2_PHASE_CORRECT_OCR0A 5

/* values for COM */
#define COM_NOTHING	0
#define COM_TOGGLE	1
#define COM_PULSE	2
#define COM_REVERSE	3


/* USART */

/* UART0 control/status register A */
#define UCSR0A		(*(uint8_t volatile *)0xC0)
#define RXC0		(1 << 7)
#define TXC0		(1 << 6)
#define UDRE0		(1 << 6)

/* UART0 control/status register B */
#define UCSR0B		(*(uint8_t volatile *)0xC1)
#define RXCIE0		(1 << 7)
#define TXCIE0		(1 << 6)
#define UDRIE0		(1 << 5)
#define RXEN0		(1 << 4)
#define TXEN0		(1 << 3)
#define UCSZ0B		(1 << 2)
#define RXB80		(1 << 1)
#define TXB80		(1 << 0)

/* UART0 control/status register C */
#define UCSR0C		(*(uint8_t volatile *)0xC2)
#define UCSZ0C(x)	((x) << 1)

/* UART0 baud rate register */
#define UBRR0		(*(uint16_t *)0xC4)

/* UART0 data register 0 */
#define UDR0		(*(uint8_t volatile *)0xC6)
