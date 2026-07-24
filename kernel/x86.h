#include "common/types.h"


struct trapframe {

    uint32_t ds;
    // pusha
    uint32_t esi;
    uint32_t ebp;
    uint32_t oesp; // useless
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    
    uint32_t trapno;
    uint32_t err;

    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
};


// Basic functions for I/O
unsigned char inb(unsigned short port)
{
    unsigned char result;

    __asm__ volatile ("in %%dx, %%al": "=a" (result): "d" (port));

    return result;

}

void outb(unsigned short port, unsigned char value)
{
    __asm__ volatile ("out %%al, %%dx": :"a" (value) ,"d" (port));
}
