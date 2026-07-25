#include "serial.h"
#include "kernel/x86.h"
#include "common/kassert.h"


void serial_init()
{
    outb(COM1+2, 0x0);  
    outb(COM1+3, 0x80); // enable DLAB
    outb(COM1,   0x03); // low divisor value
    outb(COM1,   0x0);  // high divisor value
    outb(COM1+3, 0x03); // Line protocol 8N1 
    outb(COM1+4, 0);    // Modem controll register
    outb(COM1+1, 0x01); // Enable receive interrupts.
    outb(COM1+2, 0xC7); // Enable FIFO, clear, 14-byte threshold
    outb(COM1+4, 0x0B); // IRQs disabled, RTS/DSR set
    if (inb(COM1+5) == 0xff) return; // No serial

    outb(COM1+ 4, 0x0F); // Normal operation mode

    inb(COM1+2);
    inb(COM1+0);

}


void serial_putc(char c)
{
    while(!(inb(COM1+5) & 0x20));
    outb(COM1, c);
}


void serial_print_string(const char* cstr)
{
    while(*cstr != 0)
    {
        serial_putc(*cstr);
        cstr++;
    }
}


void serial_print_uint(uint32_t num)
{
    uint8_t cstr[10] = {0};
    uint8_t len = 0;

    if (num == 0) serial_putc('0');

    while (num != 0)
    {
        cstr[len++] = num % 10;
        num /= 10;
    }


    KASSERT(len != 0);
    for (int8_t i = len-1; i >= 0; --i)
    {
        serial_putc(cstr[i] + '0');
    }
}
