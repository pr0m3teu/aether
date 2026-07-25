#include "drivers/vga.h"
#include "drivers/serial.h"
#include "util.h"

void kclear(void)
{
    vga_clear_screen();
}


void kprint(const char* cstr)
{
    vga_print_string(cstr);
}

void kpanic(const char* cstr)
{
    // First print to monitor
    serial_print_string("PANIC: ");
    if (cstr)
        serial_print_string(cstr);
    else
        serial_print_string("(no message)\n");

    serial_print_string("\n");

    // Then screen
    vga_print_string("PANIC: ");
    if (cstr)
        vga_print_string(cstr);
    else
        vga_print_string("(no message)\n");

    vga_print_string("\n");

    for(;;) {
        __asm__ volatile ("hlt");
    }
}



void kassert(_Bool cond, const char* cstr)
{
   if (!cond) kpanic(cstr); 
}
