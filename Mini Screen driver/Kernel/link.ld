ENTRY(loader) 				/* the name of the entry label */

SECTIONS {
	. = 0x00100000;		 		/* the code should be loaded at 1 MiB */

	.text ALIGN (0x1000) : 		/* align at 4 KiB */
	{
		*(.text) /* all text sections from all files */
	}

	.rodata ALIGN (0x1000) : 	/* align at 4 KiB */
	{
		*(.rodata*) /* all read-only data sections from all files */
	}

	.data ALIGN (0x1000) : 		/* align at 4 KiB */
	{
		*(.data) /* all data sections from all files */
	}

	.bss ALIGN (0x1000) :		 /* align at 4 KiB */
	{
		*(COMMON) /* all COMMON sections from all files */
		*(.bss) /* all bss sections from all files */
	}
}

/* ld -T link.ld -melf_i386 loader.o -o kernel.elf */
/* ld -melf_i386 -n -o kernel.bin -T link.ld loader.o */