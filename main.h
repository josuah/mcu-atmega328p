#define MASK32(o)		(o == 31 ? 0xFFFFFFFF : (1u << (o + 1)) - 1)
#define MASK(fld)		(MASK32(fld##_msb) ^ MASK32(fld##_lsb - 1))
#define BIT(fld)		(1u << (fld))
#define BITS(fld, val)		((uint32_t)(val) << fld##_lsb)
#define FIELD(reg, fld)		((reg) & MASK32(fld##_msb) >> fld##_lsb)

/* halt the execution */
void __stop_program(void);
