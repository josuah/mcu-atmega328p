MEMORY {
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 32K
	SRAM (rwx) : ORIGIN = 0x00800100, LENGTH = 2K
}

ENTRY(__reset_handler)

SECTIONS {
	.text : {
		KEEP(*(.vectors))
		. = ALIGN(4);
		*(.text .text.*)
		*(.rodata .rodata.*)
	} >FLASH

	.data : {
		PROVIDE(__data_start = .);
		*(.data .data.*)
		PROVIDE(__data_end = .);
	} >SRAM AT >FLASH

	.bss ADDR(.data) + SIZEOF (.data) : AT(ADDR(.bss)) {
		PROVIDE(__bss_start = .);
		*(.bss .bss.*)
		PROVIDE(__bss_end = .);
	} >SRAM

	__data_load_start = LOADADDR(.data);
	__data_load_end = __data_load_start + SIZEOF(.data);
	__stack_top = ORIGIN(SRAM) + LENGTH(SRAM);
}
