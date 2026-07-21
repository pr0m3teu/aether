#define VIDEO_MEM ((volatile char*) 0xb8000)

void kernel_entry(void)
{
    unsigned char *video_mem = (unsigned char*) VIDEO_MEM;

    char message[] = "Hello from Protected Mode!\n";
    short i = 0;
    
    while (message[i] != '\0')
    {
        video_mem[i*2] = message[i];
        video_mem[i*2 + 1] = 0x0f;
        i++;
    }

    for (;;) {
        __asm__ volatile ("hlt");
    }

}
