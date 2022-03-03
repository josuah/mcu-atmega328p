#include <stddef.h>
#include <stdint.h>

/* setup GPIO (builtin led mostly) */
void gpio_init(void);

/* enable or disable the builtin led */
void gpio_led(int onoff);

/* set pin up for all bits up in mask */
void gpio_set(uint8_t *port, uint8_t mask);

/* set pin down for all bits up in mask */
void gpio_clr(uint8_t *port, uint8_t mask);

/* setup and enable I2C */
void i2c_init(void);

/* block on reading `buf` of size `sz` from configured I2C bus from
 * device at address `addr` */
int i2c_read(uint8_t addr, uint8_t *buf, size_t sz);

/* block on writing `buf` of size `sz` to configured I2C bus to
 * device at address `addr` */
int i2c_write(uint8_t addr, uint8_t const *buf, size_t sz);

/* write an empty message for every valid address on configured I2C bus
 * until someone answers, and save its address for next call to `addr`:
 * for (uint8_t addr = 0; i2c_scan(&addr);) printf("0x%2X.n", addr); */
int i2c_scan(uint8_t *addr);

/* interrupt */
void interrupt_twi(void);

/* halt the execution */
void __stop_program(void);

/* setup GPIO (builtin led mostly) */
void gpio_init(void);

/* enable or disable the builtin led */
void gpio_led(int onoff);

/* set pin up for all bits up in mask */
void gpio_set(uint8_t *port, uint8_t mask);

/* set pin down for all bits up in mask */
void gpio_clr(uint8_t *port, uint8_t mask);

/* setup and enable I2C */
void i2c_init(void);

/* block on reading `buf` of size `sz` from configured I2C bus from
 * device at address `addr` */
int i2c_read(uint8_t addr, uint8_t *buf, size_t sz);

/* block on writing `buf` of size `sz` to configured I2C bus to
 * device at address `addr` */
int i2c_write(uint8_t addr, uint8_t const *buf, size_t sz);

/* write an empty message for every valid address on configured I2C bus
 * until someone answers, and save its address for next call to `addr`:
 * for (uint8_t addr = 0; i2c_scan(&addr);) printf("0x%2X.n", addr); */
int i2c_scan(uint8_t *addr);

/* interrupt */
void interrupt_twi(void);

/* halt the execution */
void __stop_program(void);

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

/* setup USART0 */
void uart_init(void);

/* receive a single byte through uart */
uint8_t uart_recv(void);

/* write `buf` of size `sz` through uart */
int uart_write(uint8_t const *buf, size_t sz);

/* interrupt */
void interrupt_uart(void);

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

/* setup USART0 */
void uart_init(void);

/* receive a single byte through uart */
uint8_t uart_recv(void);

/* write `buf` of size `sz` through uart */
int uart_write(uint8_t const *buf, size_t sz);

/* interrupt */
void interrupt_uart(void);
