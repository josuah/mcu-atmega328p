#include "registers.h"

#define XL	r26
#define XH	r27
#define YL	r28
#define YH	r29
#define ZL	r30
#define ZH	r31
#define zero	r1
#define FP	Y
#define FPL	YL
#define FPH	YH


.macro	.isr vector handler


.global	\vector
	\vector:

	/* save r0 and r1 first: we use them next */
	push r0
	push r1

	/* save the status register onto the stack */
	in r0, 0x3F /* SREG */
	push r0

	/* fill the "zero" register with 0 */
	clr zero

	/* save scratch registers as they might have been in use */
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	/* r28 and r29 are used as a stack pointer */
	push r30
	push r31

	/* call the actual handler: a normal C function can be used */
	call \handler

	/* restore scratch registers */
	pop r31
	pop r30
	/* r29 and r28 are used as a stack pointer */
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18

	/* restore the status register */
	pop r0
	out 0x3F, r0 /* SREG */

	/* restore r1 and r0 */
	pop r1
	pop r0

	/* clear interrupt flag and return */
	reti

	/* avr-libc jumps to 0x0000 instead of halting */
.set	\handler, __stop_program
.weak	\handler

.endm


.section .vectors


.global	__vectors
	__vectors:

	rjmp __reset_handler					/* 0x00 */
	rjmp __vector_2						/* 0x04 */
	rjmp __vector_3						/* 0x08 */
	rjmp __vector_4						/* 0x0C */
	rjmp __vector_5						/* 0x10 */
	rjmp __vector_6						/* 0x14 */
	rjmp __vector_7						/* 0x18 */
	rjmp __vector_8						/* 0x1C */
	rjmp __vector_9						/* 0x20 */
	rjmp __vector_10					/* 0x24 */
	rjmp __vector_11					/* 0x28 */
	rjmp __vector_12					/* 0x2C */
	rjmp __vector_13					/* 0x30 */
	rjmp __vector_14					/* 0x34 */
	rjmp __vector_15					/* 0x38 */
	rjmp __vector_16					/* 0x3C */
	rjmp __vector_17					/* 0x40 */
	rjmp __vector_18					/* 0x44 */
	rjmp __vector_19					/* 0x48 */
	rjmp __vector_20					/* 0x4C */
	rjmp __vector_21					/* 0x50 */
	rjmp __vector_22					/* 0x54 */
	rjmp __vector_23					/* 0x58 */
	rjmp __vector_24					/* 0x5C */
	rjmp __vector_25					/* 0x60 */
	rjmp __vector_26					/* 0x64 */


.section .text


.isr	__vector_2 interrupt_int0
.isr	__vector_3 interrupt_int1
.isr	__vector_4 interrupt_pcint0
.isr	__vector_5 interrupt_pcint1
.isr	__vector_6 interrupt_pcint2
.isr	__vector_7 interrupt_wdt
.isr	__vector_8 interrupt_timer2_compa
.isr	__vector_9 interrupt_timer2_compb
.isr	__vector_10 interrupt_timer2_ovf
.isr	__vector_11 interrupt_timer1_capt
.isr	__vector_12 interrupt_timer1_compa
.isr	__vector_13 interrupt_timer1_compb
.isr	__vector_14 interrupt_timer1_ovf
.isr	__vector_15 interrupt_timer0_compa
.isr	__vector_16 interrupt_timer0_compb
.isr	__vector_17 interrupt_timer0_ovf
.isr	__vector_18 interrupt_spi_stc
.isr	__vector_19 interrupt_usart_rx
.isr	__vector_20 interrupt_usart_udre
.isr	__vector_21 interrupt_usart_tx
.isr	__vector_22 interrupt_adc
.isr	__vector_23 interrupt_ee_ready
.isr	__vector_24 interrupt_analog_comp
.isr	__vector_25 interrupt_twi
.isr	__vector_26 interrupt_spm_ready


.global	__stop_program
	__stop_program:
 0:
	rjmp 0b

.global	sei
	sei:

	sei
	ret

.global	cli
	cli:

	cli
	ret

.global	__reset_handler
	__reset_handler:

	clr zero

	/* fallthrough */
 __copy_data:
	ldi ZL, lo8(__data_load_start)
	ldi ZH, hi8(__data_load_start)
	ldi XL, lo8(__data_start)
	ldi XH, hi8(__data_start)

	rjmp 1f
 0:
	/* Load a byte from Program Memory (ROM) */
	lpm r0, Z+

	/* Store it to the RAM */
	st X+, r0
 1:
	/* done yet? */
	cpi XL, lo8(__data_end)
	brne 0b
	cpi XH, hi8(__data_end)
	brne 0b

	/* fallthrough */
 __clear_bss:
	ldi ZH, hi8(__bss_start)
	ldi ZL, lo8(__bss_start)

	rjmp 1f
 0:
	/* fill the stack with one more 0 */
	st Z+, zero
 1:
	/* done yet? */
	cpi ZL, lo8(__bss_end)
	brne 0b
	cpi ZH, hi8(__bss_end)
	brne 0b

	/* fallthrough */
 __call_main:
	call main
	rjmp __stop_program


.section .fuses


.weak	__fuses
	__fuses:

	/* low fuse bits */
.byte	LFUSE(FON*CKDIV8 | FOFF*CKOUT | SUT_SLOW | CKSEL_CERAMIC_CALIB)

	/* high fuse bits */
.byte	HFUSE(FOFF*RSTDISBL | FOFF*DWEN | FON*SPIEN | FOFF*WDTON |
	FOFF*EESAVE | BOOTSZ_2048 | FOFF*BOOTRST)

	/* extended fuse bits */
.byte	EFUSE(BODLEVEL_OFF)
