
void kernel_entry(void)
{
    for (;;) {
        __asm__ volatile ("hlt");
    }
}
