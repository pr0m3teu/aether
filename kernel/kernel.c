#include "common/kassert.h"
#include "common/util.h"
#include "drivers/serial.h"

#include "interrupts.h"
#include "pic.h"

__attribute__((section(".text.boot"))) // Small hack for now
void kernel_entry(void)
{
    serial_init();
    idt_init();
    pic_init();

    kclear();
    kprint("Welcome to Project Aether\n");
    kprint("Hello from Protected Mode!\n");
    kprint("> ");


    for (;;) {
        __asm__ volatile ("hlt");
    }

}
