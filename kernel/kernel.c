#include "vga_driver.h"

__attribute__((section(".text.boot"))) // Small hack for now
void kernel_entry(void)
{
    char message[] = "Hello from Protected Mode!\n";

    vga_clear_screen();
    vga_print_string(message);
    vga_print_string("This should also be on a new line\n");

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
