#include "drivers/vga_driver"
#include "interrupts.h"


void exception_handler()
{
    vga_print_string("EXCEPTION\n");
    __asm__ volatile("cli; hlt");
}

