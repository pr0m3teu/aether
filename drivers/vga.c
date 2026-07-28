#include "vga.h"
#include "arch/x86.h"


void vga_set_cursor(uint16_t offset)
{
    outb(VGA_CRT_INDEX, VGA_CURSOR_HIGH);

    uint8_t high_byte = (offset >> 8);
    outb(VGA_CRT_DATA, high_byte);

    uint8_t low_byte =  (offset & 0xff);

    outb(VGA_CRT_INDEX, VGA_CURSOR_LOW);
    outb(VGA_CRT_DATA, low_byte);
}


uint16_t vga_get_cursor()
{
    uint16_t cursor;
    uint8_t  curr_byte;

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
    for (uint16_t i = 0; i < VGA_COLS * VGA_LINES; ++i)
    {
        VGA_VIDEO_MEM[i * 2] = ' ';
        VGA_VIDEO_MEM[i * 2 + 1] = VGA_WHITE;
    }
    vga_set_cursor(0);
}


void vga_putc(char c)
{ 
    uint16_t cursor = vga_get_cursor();
    if (cursor >= VGA_COLS * VGA_LINES)
    {
        for (uint16_t i = VGA_LINES; i < VGA_COLS * VGA_LINES; ++i)
        {
            VGA_VIDEO_MEM[i * 2]     = VGA_VIDEO_MEM[(i + VGA_COLS) * 2];
            VGA_VIDEO_MEM[i * 2 + 1] = VGA_VIDEO_MEM[(i + VGA_COLS) * 2 + 1];
        }
        for (uint16_t i = VGA_COLS * (VGA_LINES - 1); i < VGA_COLS * VGA_LINES; ++i)
        {
            VGA_VIDEO_MEM[i * 2]     = ' ';
            VGA_VIDEO_MEM[i * 2 + 1] = VGA_WHITE;
        }
        vga_set_cursor((VGA_LINES-1) * VGA_COLS);
        cursor = (VGA_LINES-1) * VGA_COLS; 
    }

    if (c == '\n')
    {
        vga_set_cursor(cursor + (VGA_COLS - cursor % VGA_COLS));
        return;
    }
    VGA_VIDEO_MEM[cursor << 1] = c;
    VGA_VIDEO_MEM[(cursor << 1) + 1] = VGA_WHITE;
    vga_set_cursor(cursor + 1);
}


uint32_t vga_print_string(const char * cstr)
{
    uint32_t i = 0;
    while (cstr[i] != 0)
    {
        vga_putc(cstr[i]);
        i++;
    }
    return i;
}

void vga_init()
{
    vga_clear_screen();
}

uint32_t vga_write(const uint8_t *buf, uint32_t len)
{
    (void) len;
    return vga_print_string((const char*) buf);
}

struct driver_ops vga_ops = {
    .name  = "VGA Text Mode",
    .init  = &vga_init,
    .write = &vga_write,
    .read  = 0,
};


