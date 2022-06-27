#include "libatmega328p.h"

.macro	.isr name
.global	__vector_\name
	__vector_\name:

	/* save r1 first: we use them next */
	push r1

	/* save the status register onto the stack */
	in r1, 0x3F /* SREG */
	push r1

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

	/* call the actual interrupt handler*/
	call __interrupt_\name

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
	pop r1
	out 0x3F, r1 /* SREG */

	/* restore r1 */
	pop r1

	reti
.endm

.section .vectors

.global	__vectors
	__vectors:
	rjmp __reset_handler
	rjmp __null_handler ; __vector_int0
	rjmp __null_handler ; __vector_int1
	rjmp __null_handler ; __vector_pcint0
	rjmp __null_handler ; __vector_pcint1
	rjmp __null_handler ; __vector_pcint2
	rjmp __null_handler ; __vector_wdt
	rjmp __null_handler ; __vector_timer2_compa
	rjmp __null_handler ; __vector_timer2_compb
	rjmp __null_handler ; __vector_timer2_ovf
	rjmp __null_handler ; __vector_timer1_capt
	rjmp __null_handler ; __vector_timer1_compa
	rjmp __null_handler ; __vector_timer1_compb
	rjmp __null_handler ; __vector_timer1_ovf
	rjmp __null_handler ; __vector_timer0_compa
	rjmp __null_handler ; __vector_timer0_compb
	rjmp __vector_twi   ; __vector_timer0_ovf
	rjmp __null_handler ; __vector_spi_stc
	rjmp __null_handler ; __vector_usart_rx
	rjmp __null_handler ; __vector_usart_udre
	rjmp __null_handler ; __vector_usart_tx
	rjmp __null_handler ; __vector_adc
	rjmp __null_handler ; __vector_ee_ready
	rjmp __null_handler ; __vector_analog_comp
	rjmp __null_handler ; __vector_twi
	rjmp __null_handler ; __vector_spm_ready

;.isr	int0
;.isr	int1
;.isr	pcint0
;.isr	pcint1
;.isr	pcint2
;.isr	wdt
;.isr	timer2_compa
;.isr	timer2_compb
;.isr	timer2_ovf
;.isr	timer1_capt
;.isr	timer1_compa
;.isr	timer1_compb
;.isr	timer1_ovf
;.isr	timer0_compa
;.isr	timer0_compb
;.isr	timer0_ovf
;.isr	spi_stc
;.isr	usart_rx
;.isr	usart_udre
;.isr	usart_tx
;.isr	adc
;.isr	ee_ready
;.isr	analog_comp
.isr	twi
;.isr	spm_ready

.section .text

.global	sei
	sei:
	sei
	ret

.global	cli
	cli:
	cli
	ret
