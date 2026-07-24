#include "common/util.h"

#include "interrupts.h"

__attribute__((section(".text.boot"))) // Small hack for now
void kernel_entry(void)
{
    idt_init();
    char message[] = "Hello from Protected Mode!\n";

    kclear();
    kprint("Welcome to Project Aether\n");
    kprint(message);
    kprint("> ");

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
