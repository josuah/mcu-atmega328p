#include <stddef.h>
#include <stdint.h>

#define STATIC_ASSERT(exp) typedef char failed[(exp) ? 1 : -1]

#define CPU_FREQ	16000000ul

/* assert that an expression is true or halt the program */
void runtime_assert(int expr);

/* set interrupts */
void sei(void);

/* clear interrupts */
void cli(void);

/* halt the execution */
void __stop_program(void);
