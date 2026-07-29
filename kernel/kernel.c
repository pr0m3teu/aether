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

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
