#include "common/kassert.h"
#include "common/util.h"
#include "drivers/serial.h"

#include "interrupts.h"
#include "pic.h"

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
    serial_init();
    idt_init();
    pic_init();
    sti();

    kclear();
    kprint("Welcome to Project Aether\n");
    kprint("Hello from Protected Mode!\n");
    kprint("> ");


    for (;;) {
        __asm__ volatile ("hlt");
    }

}
