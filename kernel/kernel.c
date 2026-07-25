#include "common/kassert.h"
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

    kclear();
    kprint("Welcome to Project Aether\n");
    kprint("Hello from Protected Mode!\n");
    kprint("> ");
    KASSERT(2 + 2 == 5);

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
