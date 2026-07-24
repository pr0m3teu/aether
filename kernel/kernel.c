#include "drivers/vga_driver.h"

#include "interrupts.h"

__attribute__((section(".text.boot"))) // Small hack for now
void kernel_entry(void)
{
    idt_init();
    char message[] = "Hello from Protected Mode!\n";

    vga_clear_screen();
    vga_print_string("Welcome to Project Aether\n");
    vga_print_string(message);
    vga_print_string("> ");

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
