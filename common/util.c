#include "drivers/vga.h"
#include "util.h"

void kclear(void)
{
    vga_clear_screen();
}


void kprint(const char* cstr)
{
    vga_print_string(cstr);
}
