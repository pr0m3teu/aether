#include "drivers/vga.h"
#include "drivers/serial.h"
#include "util.h"
#include "kassert.h"

void kclear(void)
{
    vga_clear_screen();
}


void kprint(const char* cstr)
{
    KASSERT(cstr != 0);
    vga_print_string(cstr);
}


void kpanic(const char* cstr)
{
#ifdef SERIAL_PANIC
    // First print to monitor
    serial_print_string("\nPANIC: ");
    if (cstr)
        serial_print_string(cstr);
    else
        serial_print_string("(no message)\n");

    serial_print_string("\n");
#endif
    // Then screen
    vga_print_string("\nPANIC: ");
    if (cstr)
        vga_print_string(cstr);
    else
        vga_print_string("(no message)\n");

    vga_print_string("\n");

    for(;;) {
        __asm__ volatile ("hlt");
    }
}


