ENTRY(kernel_entry)

SECTIONS
{
    . = 0x100000;

    .text : {
        *(.text.boot)
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    .data : {
        *(.data)
    }

    .bss : {
        __bss_start = .;
        *(.bss)
        __bss_end   = .;
    }
}
