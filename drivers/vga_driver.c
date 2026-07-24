#define BASIC_IMPLEMENTATIONS
#include "kernel/x86.h"
#include "vga_driver.h"


void vga_set_cursor(unsigned short offset)
{
    outb(VGA_CRT_INDEX, VGA_CURSOR_HIGH);

    unsigned char high_byte = (offset >> 8);
    outb(VGA_CRT_DATA, high_byte);

    unsigned char low_byte =  (offset & 0xff);

    outb(VGA_CRT_INDEX, VGA_CURSOR_LOW);
    outb(VGA_CRT_DATA, low_byte);
}


unsigned short vga_get_cursor()
{
    unsigned short cursor;
    unsigned char  curr_byte;

    outb(VGA_CRT_INDEX, VGA_CURSOR_HIGH);
    curr_byte = inb(VGA_CRT_DATA);
    cursor = curr_byte << 8;

    outb(VGA_CRT_INDEX, VGA_CURSOR_LOW);
    curr_byte = inb(VGA_CRT_DATA);
    cursor |= curr_byte;

    return cursor;
}


void vga_clear_screen()
{
    for (unsigned short i = 0; i < VGA_COLS * VGA_LINES; ++i)
    {
        VGA_VIDEO_MEM[i * 2] = ' ';
        VGA_VIDEO_MEM[i * 2 + 1] = VGA_WHITE;
    }
    vga_set_cursor(0);
}


void vga_putc(char c)
{ 
    unsigned short cursor = vga_get_cursor();

    if (c == '\n')
    {
        vga_set_cursor(cursor + (VGA_COLS - cursor % VGA_COLS));
        return;
    }
    VGA_VIDEO_MEM[cursor << 1] = c;
    VGA_VIDEO_MEM[(cursor << 1) + 1] = VGA_WHITE;
    vga_set_cursor(cursor + 1);
}


int vga_print_string(const char * cstring)
{
    int i = 0;
    while (cstring[i] != 0)
    {
        vga_putc(cstring[i]);
        i++;
    }
    return i;
}


