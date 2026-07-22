// Basic functions for I/O

unsigned char in(unsigned short port)
{
    unsigned char result;

    __asm__ volatile ("in %%dx, %%al": "=a" (result): "d" (port));

    return result;

}

void out(unsigned short port, unsigned char value)
{
    __asm__ volatile ("out %%al, %%dx": :"a" (value) ,"d" (port));
}
