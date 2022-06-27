#ifndef LIBSSD1306_H
#define LIBSSD1306_H


/* set to a function writing `buf` of size `sz` to `addr` over I2C */
extern int ssd1306_fn_i2c_write(uint8_t addr, uint8_t const *buf, size_t sz);

/* send control commands to the screen to make it ready to draw */
static int ssd1306_init(void);

/* print a dot on the internal buffer at coordinamtes (x, y) */
static void ssd1306_draw_point(uint16_t x, uint16_t y);

/* reset the software buffer to 0x00: clear the screen */
static void ssd1306_clear(void);

/* send the buffer to the actual screen backend */
static int ssd1306_flush(void);


/// POLICE LINE /// DO NOT CROSS ///


/* screen height in pixels */
#ifndef SSD1306_ROWS
#define SSD1306_ROWS	32
#endif

/* screen width in pixels */
#ifndef SSD1306_COLS
#define SSD1306_COLS	128
#endif

/* can be changed hardware-side, often by soldering an extra pin to ground */
#ifndef SSD1306_I2C_ADDR
#define SSD1306_I2C_ADDR 0x3C
#endif

/* i2c packets for filling the R/S pin with 0/1 */
#define	SSD1306_CTRL (0<<7 | 0<<6)
#define	SSD1306_DATA (0<<7 | 1<<6)

#define SSD1306_SET_MODE 0x20
#define SSD1306_MODE_HORIZ 0
#define SSD1306_MODE_VERT 1
#define SSD1306_MODE_PAGE 2

#define SSD1306_SET_PAGE_RANGE 0x22

#define SSD1306_SET_POS 0x40

#define SSD1306_SET_CONTRAST 0x81

#define SSD1306_SET_PUMP 0x8D
#define SSD1306_PUMP_ON 0x14

#define SSD1306_SET_ALL_RAM 0xA4
#define SSD1306_SET_ALL_ON 0xA5

#define SSD1306_SET_INV_OFF 0xA6
#define SSD1306_SET_INV_ON 0xA7

#define SSD1306_SET_DISP_OFF 0xAE
#define SSD1306_SET_DISP_ON 0xAF

#define SSD1306_SET_CLOCK 0xD5
#define SSD1306_CLOCK_DIVIDE (0<<0)
#define SSD1306_CLOCK_FREQ (15<<4)

#define SSD1306_SET_COM_PIN 0xDA
#define SSD1306_COM_PIN_ALT_NO_REMAP 0x02

#define SSD1306_SET_COM_0_TO_N 0xC0
#define SSD1306_SET_COM_N_TO_0 0xC8

#define SSD1306_SET_REMAP_0 0xA0
#define SSD1306_SET_REMAP_127 0xA1

#define SSD1306_SET_OFFSET 0xD3
#define SSD1306_SET_MULTIPLEX 0xA8

static uint8_t pixbuf[1 + SSD1306_ROWS/8 * SSD1306_COLS];

/*
 * scanning is configured by init() to go this way:
 *
 *	<------COLS------->		Seg: 8bit vertical line
 *	000 008 010 ... 3F0     ^	Row: 8bit high, COLS wide
 *	 : / : / :  ...  : }Seg |
 *	007 00F 017 ... 3FF     |
 *	 ,- - - - - - - -'	|
 *	400 408 410 ... 7F0     ROWS
 *	 : / : / :  ...  :      |
 *	407 40F 417 ... 7FF     |
 *	 ,- - - - - - - -'	|
 *	 :   :   :  ...  :      :
 */
static int
ssd1306_init(void)
{
	static const uint8_t buf[] = {
		SSD1306_CTRL,

		/* only first half of the screen */
		SSD1306_SET_PAGE_RANGE, 0, SSD1306_ROWS / 8 - 1,

		/* rule for selecting the next segment to write
		 * pixels to */
		SSD1306_SET_MODE, SSD1306_MODE_HORIZ,

		/* seems to be required or the screen stays balck
		 * maybe related to how the pins are connected to
		 * the PCB */
		SSD1306_SET_COM_PIN, SSD1306_COM_PIN_ALT_NO_REMAP,

		/* support 5V instead of 7/12V min */
		SSD1306_SET_PUMP, SSD1306_PUMP_ON,

		/* only works after pump configured */
		SSD1306_SET_DISP_ON,
	};

	ssd1306_clear();
	if (ssd1306_fn_i2c_write(SSD1306_I2C_ADDR, buf, sizeof buf) == -1)
		return -1;
	return ssd1306_flush();
}

static int
ssd1306_flush(void)
{
	return ssd1306_fn_i2c_write(SSD1306_I2C_ADDR, pixbuf, sizeof pixbuf);
}

static void
ssd1306_clear(void)
{
	memset(pixbuf, 0x00, sizeof pixbuf);
	pixbuf[0] = SSD1306_DATA;  /* rest of the buffer for data */
}

static void
ssd1306_draw_point(uint16_t x, uint16_t y)
{
	uint8_t *seg;

	if (x >= SSD1306_COLS || y >= SSD1306_ROWS)
		return;
	seg = pixbuf + 1 + y/8 * SSD1306_COLS + x;
	assert(seg < pixbuf + sizeof pixbuf);
	*seg |= 1<<(y % 8);
}

#endif
