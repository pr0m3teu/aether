#include "common/types.h"
#include "common/util.h"

#include "drivers/vga.h"

uint8_t curr = 0; // TODO: Verify bug where this variable cannot be made static inside consoleintr
static char line_buf[256];
void consoleintr(char (*getc)(void))
{
    char ch;
    while ((ch = getc()) > 0)
    {
        switch(ch)
        {
            case '\n':
                if (curr > 0) kputc('\n');
                line_buf[curr] = '\0';
                kprint(line_buf);
                kprint("\n> ");
                curr = 0;
                break;
            
            case '\b':
                uint16_t cursor = vga_get_cursor();
                vga_set_cursor(cursor-1);
                vga_putc(' ');
                vga_set_cursor(cursor-1);
                curr--;
                break;
            case -1:
                break;

            default:
                line_buf[curr++] = ch;
                kputc(ch);
                break;
        }
    }
}
