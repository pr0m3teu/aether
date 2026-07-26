#include "drivers/serial.h"
#include "common/util.h"

#include "pic.h"

void pic_eoi(uint8_t irq)
{
    KASSERT(irq < 16);
    if (irq < 8)
    {
        outb(PIC1_COMMAND, PIC_EOI);
        return;
    }
    outb(PIC2_COMMAND, PIC_EOI);
}


// Offsets are the ICW2 in this case
void pic_remap(uint8_t pic1_offset, uint8_t pic2_offset)
{
    if (pic1_offset < 0x20 || pic2_offset < 0x20) kpanic("pic_remap");

    outb(PIC1_COMMAND, ICW1);
    outb(PIC2_COMMAND, ICW1);

    outb(PIC1_DATA, pic1_offset); // ICW2
    outb(PIC2_DATA, pic2_offset); // ICW2

    outb(PIC1_DATA, 1 << CASCADE_IRQ); // ICW3
    outb(PIC2_DATA, CASCADE_IRQ);      // ICW3

    outb(PIC1_DATA, ICW4);   
    outb(PIC2_DATA, ICW4);   

    outb(PIC1_DATA, 0x0); // Unmask
    outb(PIC2_DATA, 0x0); // Unmask
}

static inline void pic_dissable(void)
{
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}

void pic_mask(uint8_t irq)
{
    KASSERT(irq < 16);

    uint16_t port;
    if (irq < 8) {
        port = PIC1_DATA;
    }
    else {
        port = PIC2_DATA;
        irq -= 8;
    }

    uint8_t mask = inb(port);
    outb(port, mask | (1 << irq)); 
}

void pic_unmask(uint8_t irq)
{
    KASSERT(irq < 16);
    uint16_t port;
    if (irq < 8) {
        port = PIC1_DATA;
    }
    else {
        port = PIC2_DATA;
        irq -= 8;
    }
    uint8_t mask = inb(port);
    outb(port, mask & ~(1 << irq));
}

void pic_init()
{
    pic_remap(0x20, 0x28);
    pic_dissable();
    
    pic_unmask(0x2); // enable slave
    pic_unmask(0x1); // keyboard

    serial_print_string("[info] Initialized PIC\n");
}
