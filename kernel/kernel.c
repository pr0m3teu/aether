#include "common/util.h"
#include "drivers/serial.h"

#include "interrupts.h"

__attribute__((section(".text.boot"))) // Small hack for now
void kernel_entry(void)
{
    serial_init();
    idt_init();
    char message[] = "Hello from Protected Mode!\n";

    kclear();
    kprint("Welcome to Project Aether\n");
    kprint(message);
    kprint("> ");
    serial_print("Hello Serial!\n");

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
