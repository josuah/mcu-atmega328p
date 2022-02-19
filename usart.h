#include <stddef.h>
#include <stdint.h>

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

/* setup USART0 */
void uart_init(void);

/* receive a single byte through uart */
uint8_t uart_recv(void);

/* write `buf` of size `sz` through uart */
int uart_write(uint8_t const *buf, size_t sz);

/* interrupt */
void interrupt_uart(void);
