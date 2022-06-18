#ifndef LIBC_H
#define LIBC_H

/* <stddef.h> */

#define NULL ((void *)0)
typedef unsigned int size_t;
typedef signed int ssize_t;

/* <stdint.h> */

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef unsigned long	uint64_t;
typedef signed char	int8_t;
typedef signed short	int16_t;
typedef signed int	int32_t;
typedef signed long	int64_t;
#define UINT8_MAX	0xFFu
#define UINT16_MAX	0xFFFFul
#define UINT32_MAX	0xFFFFFFFFul
#define UINT64_MAX	0xFFFFFFFFFFFFFFFFull

/* <time.h> */

typedef uint64_t	time_t;

/* <string.h> */

void *memset(void *mem, int val, size_t sz);
size_t strlen(char const *str);

/* <assert.h> */

#ifdef NDEBUG
#define assert(expr)	0
#else /* endless loop visible in-place with a debugger */
#define assert(expr)	if (!(expr)) for (;;) alert()
#endif

/* provided by the programmer for blinking a led or anything */
void alert(void);

/* <ctype.h> */

int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);

/* <util.h> */

char *fmtint(char *s, size_t sz, int64_t i64, uint8_t b);

/* <arpa/inet.h> */

uint32_t htonl(uint32_t u32);

#endif
