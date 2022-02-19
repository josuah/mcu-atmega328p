#include <stddef.h>
#include <stdint.h>

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

/* (r-) timer/counter 2 counter value */
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

/* setup timer */
void timer0_init(int cs, int mode);
void timer1_init(int cs, int mode);
void timer2_init(int cs, int mode);

/* get current time in microsecond */
uint64_t timer_gettime(void);

/* sleep for `us` microseconds */
void timer_sleep(uint64_t us);

/* enable/disable interrupt for timer `timer` */
void timer_set_interrupt(int timer);

/* interrupt */
void interrupt_timer0_ovf(void);
void interrupt_timer1_ovf(void);
void interrupt_timer2_ovf(void);
