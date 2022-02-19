#include <stddef.h>
#include <stdint.h>

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
