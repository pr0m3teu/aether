#ifndef PIC_H_
#define PIC_H_

#include "common/types.h"
#include "common/kassert.h"
#include "arch/x86.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21

#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

#define PIC_EOI      0x20
#define ICW1         0x11
#define ICW4         0x01

#define CASCADE_IRQ  0x02


void pic_eoi(uint8_t irq);
void pic_remap(uint8_t pic1_offset, uint8_t pic2_offset);
void pic_init(void);

#endif
