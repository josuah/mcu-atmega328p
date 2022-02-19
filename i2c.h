#include <stddef.h>
#include <stdint.h>

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
