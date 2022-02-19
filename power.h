#include <stddef.h>
#include <stdint.h>

/* power reduction register */
#define PRR		(*(uint8_t volatile *)0x64)
#define PRTWI		(1 << 7)
#define PRTIM2		(1 << 6)
#define PRTIM0		(1 << 5)
#define PRTIM1		(1 << 3)
#define PRSPI		(1 << 2)
#define PRUSAR0		(1 << 1)
#define PRADC		(1 << 0)
