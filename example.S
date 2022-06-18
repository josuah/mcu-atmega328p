; consider that I am a beginner, and taking the below as a model has some risk

PORTB = 0x05
DDRB = 0x04

.org 0x00

.global	main
	main:

	; set pin direction to 'out'
	ldi	r24, 1 << 5
	out	DDRB, r24

	; set pin to 1
	ldi	r24, 1 << 5
	out	PORTB, r24
