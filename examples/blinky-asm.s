; consider that I am a beginner, and taking the below as a model has some risk

PortB = 0x05
DdrB = 0x04
Pin5 = (1<<5)

busywait:
	push	r18
	push	r19
	push	r20

	; accumulate enough counters to wait about 1s
	ldi	r18, 0x00
	ldi	r19, 0x00
	ldi	r20, 0x10
 0:
	subi	r18, 1
	brne	0b
	subi	r19, 1
	brne	0b
	subi	r20, 1
	brne	0b

	pop	r20
	pop	r19
	pop	r18
	ret

.global main
main:
	; set pin direction to 'out'
	ldi	r24, Pin5
	out	DdrB, r24

	; set pin to 1
	ldi	r24, Pin5
	out	PortB, r24
	rcall	busywait
	rcall	busywait
	rcall	busywait
	rcall	busywait
	rcall	busywait
	rcall	busywait
	rcall	busywait
	rcall	busywait

	rjmp	blink

blink:
	; set pin direction to 'out'
	ldi	r24, Pin5
	out	DdrB, r24
 0:
	; set pin to 0
	out	PortB, r0
	rcall	busywait

	; set pin to 1
	ldi	r24, Pin5
	out	PortB, r24
	rcall	busywait

	rjmp	0b
