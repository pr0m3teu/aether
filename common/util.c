#include "kernel/x86.h"
#include "drivers/vga.h"
#include "drivers/serial.h"
#include "util.h"
#include "kassert.h"

void kclear(void)
{
    vga_clear_screen();
}


void kputc(char c)
{
    vga_putc(c);
}


void kprint(const char* cstr)
{
    KASSERT(cstr != 0);
    vga_print_string(cstr);
}


void kprint_uint(uint32_t num)
{
    uint8_t cstr[10] = {0};
    uint8_t len = 0;

    if (num == 0) kputc('0');

    while (num != 0)
    {
        cstr[len++] = num % 10;
        num /= 10;
    }

    KASSERT(len != 0);
    for (int8_t i = len-1; i >= 0; --i)
    {
        kputc(cstr[i] + '0');
    }
}


void kpanic(const char* cstr)
{
#ifdef SERIAL_PANIC
    // First print to monitor
    serial_print_string("\n(PANIC): ");
    if (cstr)
        serial_print_string(cstr);
    else
        serial_print_string("(no message)\n");

    serial_print_string("\n");
#endif
    // Then screen
    vga_print_string("\n(PANIC): ");
    if (cstr)
        vga_print_string(cstr);
    else
        vga_print_string("(no message)\n");

    vga_print_string("\n");

    cli();
    for(;;) {
        __asm__ volatile ("hlt");
    }
}


