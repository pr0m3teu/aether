#include "common/util.h"
#include "drivers/serial.h"

#include "interrupts.h"

__attribute__((section(".text.boot"))) // Small hack for now
void kernel_entry(void)
{
    serial_init();
    serial_print_string("[info] Initialized Serial COM\n");
    idt_init();
    serial_print_string("[info] Initialized Interrupt Descriptor Table\n");
    char message[] = "Hello from Protected Mode!\n";

    kclear();
    kprint("Welcome to Project Aether\n");
    kprint(message);
    kprint("> ");

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
