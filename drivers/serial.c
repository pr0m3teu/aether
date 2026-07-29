#include "serial.h"
#include "arch/x86.h"
#include "common/kassert.h"


void serial_init()
{
    outb(COM1+2, 0x0);  
    io_wait();
    outb(COM1+3, 0x80); // enable DLAB
    io_wait();
    outb(COM1,   0x03); // low divisor value
    io_wait();
    outb(COM1,   0x0);  // high divisor value
    io_wait();
    outb(COM1+3, 0x03); // Line protocol 8N1 
    io_wait();
    outb(COM1+4, 0);    // Modem controll register
    io_wait();
    outb(COM1+1, 0x01); // Enable receive interrupts.
    io_wait();
    outb(COM1+2, 0xC7); // Enable FIFO, clear, 14-byte threshold
    io_wait();
    outb(COM1+4, 0x0B); // IRQs disabled, RTS/DSR set
    io_wait();
    if (inb(COM1+5) == 0xff) return; // No serial

    outb(COM1+ 4, 0x0F); // Normal operation mode
    io_wait();

    inb(COM1+2);
    inb(COM1+0);

    serial_print_string("[info] Initialized Serial COM\n");
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

uint32_t serial_write(const uint8_t* buf, uint32_t len)
{
    serial_print_string((const char*)buf);
    return len;
}

struct driver_ops serial_ops = {
    .name  = "Serial output",
    .init  = &serial_init,
    .write = &serial_write,
    .read  = 0,
};


