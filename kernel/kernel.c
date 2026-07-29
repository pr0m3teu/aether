#include "common/kassert.h"
#include "common/util.h"
#include "drivers/driver.h"
#include "drivers/vga.h"
#include "drivers/serial.h"
#include "drivers/kbd.h"

#include "interrupts.h"
#include "pic.h"

static struct driver_ops *drivers[] = { &vga_ops, &serial_ops, &kbd_ops, 0 };

extern uint32_t __bss_start;
extern uint32_t __bss_end;
void zero_bss()
{
    uint32_t *start = (uint32_t *)&__bss_start;
    uint32_t *end   = (uint32_t *)&__bss_end;

    while (start != end)
    {
        *start = 0x0;
        ++start;
    }
}

__attribute__((section(".text.boot"))) // Small hack for now
void kernel_entry(void)
{
    zero_bss();
    drivers_init(drivers);
    idt_init();
    pic_init();
    sti();

    kprint("Welcome to Project Aether\n");
    kprint("Hello from Protected Mode!\n");
    kprint("> ");
    uint8_t run = 1;
    char line_buf[256] = {0};
    uint8_t curr = 0;
    while (run)
    {
        char ch = kbd_get_char();
        switch(ch)
        {
            case -1:
                break;
            case 27: // ESC 
                run = 0;
                break;
            case '\n':
                kputc('\n');
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

            default:
                line_buf[curr++] = ch;
                kputc(ch);
                break;
        }
    }

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
