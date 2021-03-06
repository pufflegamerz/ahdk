OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(start)

#ifdef STANDALONE
	// Attempt to run AHDK on 
	// address independent code (pie)
	SECTIONS {
		. = ALIGN(4);
		.rel.dyn : {
			*(.rel.dyn)
		}

		. = ALIGN(4);
		.rodata : {
			*(.rodata*)
		}

		. = ALIGN(4);
		.data : {
			DATA_START = .;
			*(.data*)
			DATA_END = .;
		}
	}
#else
	// Problems:
	// - global integers with preset values not working
	// - Exposure app issue, see apps.c
	// In other words, I have no idea how to write linker scripts. :)

	SECTIONS {
		// GCC will preprocess MEM_MAIN into an address
		.text MEM_MAIN: {
			*(.text)
		}
	}
#endif