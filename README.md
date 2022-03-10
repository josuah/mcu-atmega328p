ATmega328P
==========
<https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf>

MCU with [AVR](/avr-architecture/) 8-bit architecture.

![ATmega328P on Elegoo Nano](/image/atmega328p.jpg)

Can still use 16-bit addresses through "pointer registers" pair of
register splitting upper and lower bits:
`X` (`R26` low, `R27` high),
`Y` (`R28` low, `R29` high),
`Z` (`R30` low, `R31` high).

IO(0x0000-0x001F) - IO Space
----------------------------
Addresses for communicating through the MCU pins.
Every bit are mapping to one pin, grouped into ports.

* The instructions `SBI` and `CBI` permit to read/write for a whole port.
* The instructions `SSBI` and `SCBI` permit to read/write for a single pin.
* The instructions `IN` and `OUT` permit to read/write for these
  ports specifically.

> When using the I/O specific commands IN and OUT, the I/O addresses
> 0x00 - 0x3F must be used.
> When addressing I/O registers as data space using LD and ST
> instructions, 0x20 must be added to these addresses.

Encountered as `#define __SFR_OFFSET 0x20` in `<avr/sfr_defs.h>`.

IO(0x003E-0x003F) - Stack pointer
---------------------------------
16-bit address to the top of the stack, which must be set before the stack
memory gets used. By default, the `crt.o` file for the ATmega328p of AVR-gcc
is already setting it (used from C and ASM), so no need to set it by hand:

```
$ avr-objdump -d -j .init2 avr/lib/avr5/crtatmega328p.o

00000000 <.init2>:
   0:   11 24           eor     r1, r1
   2:   1f be           out     0x3f, r1        ; SREG = 0x01
   4:   c0 e0           ldi     r28, 0x00       ; 0
   6:   d0 e0           ldi     r29, 0x00       ; 0
   8:   de bf           out     0x3e, r29       ; SPL = 0x00
   a:   cd bf           out     0x3d, r28       ; SPH = 0x00
```

PROG(0x0000-0x0032) - Interrupt handlers addresses
--------------------------------------------------
* 0x0000 - `RESET` - External pin, power-on reset, brown-out reset and watchdog system reset
* 0x0002 - `INT0` - External interrupt request 0
* 0x0004 - `INT1` - External interrupt request 1
* 0x0006 - `PCINT0` - Pin change interrupt request 0
* 0x0008 - `PCINT1` - Pin change interrupt request 1
* 0x000A - `PCINT2` - Pin change interrupt request 2
* 0x000C - `WDT` - Watchdog time-out interrupt
* 0x000E - `TIMER2 COMPA` - Timer/Counter2 compare match A
* 0x0010 - `TIMER2 COMPB` - Timer/Counter2 compare match B
* 0x0012 - `TIMER2 OVF` - Timer/Counter2 overflow
* 0x0014 - `TIMER1 CAPT` - Timer/Counter1 capture event
* 0x0016 - `TIMER1 COMPA` - Timer/Counter1 compare match A
* 0x0018 - `TIMER1 COMPB` - Timer/Counter1 compare match B
* 0x001A - `TIMER1 OVF` - Timer/Counter1 overflow
* 0x001C - `TIMER0 COMPA` - Timer/Counter0 compare match A
* 0x001E - `TIMER0 COMPB` - Timer/Counter0 compare match B
* 0x0020 - `TIMER0 OVF` - Timer/Counter0 overflow
* 0x0022 - `SPI`, `STC` - SPI serial transfer complete
* 0x0024 - `USART`, `RX` - USART Rx complete
* 0x0026 - `USART`, `UDRE` - USART, data register empty
* 0x0028 - `USART`, `TX` - USART, Tx complete
* 0x002A - `ADC` - ADC conversion complete
* 0x002C - `EE READY` - EEPROM ready
* 0x002E - `ANALOG COMP` - Analog comparator
* 0x0030 - `TWI` - 2-wire serial interface
* 0x0032 - `SPM READY` - Store program memory ready
