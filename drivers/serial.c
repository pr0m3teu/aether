#include "serial.h"
#include "kernel/x86.h"


void serial_init()
{
    outb(COM1+2, 0x0);  
    outb(COM1+3, 0x80); // enable DLAB
    outb(COM1,   0x03); // low divisor value
    outb(COM1,   0x0);  // high divisor value
    outb(COM1+3, 0x03); // Line protocol 8N1 
    outb(COM1+4, 0);    // Modem controll register
    outb(COM1+1, 0x01); // Enable receive interrupts.

    if (inb(COM1+5) == 0xff) return; // No serial

    outb(COM1+ 4, 0x0F); // Normal operation mode

    inb(COM1+2);
    inb(COM1+0);

}


void serial_write(char c)
{
    while(!(inb(COM1+5) & 0x20));
    outb(COM1, c);
}


void serial_print(const char* cstr)
{
    while(*cstr != 0)
    {
        serial_write(*cstr);
        cstr++;
    }
}
