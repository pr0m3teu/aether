#include "drivers/vga_driver.h"

#include "interrupts.h"

__attribute__((aligned(0x10))) 
static struct gatedesc idt[MAX_INTS];

static struct idtr_s idtr = {0};

static void idt_set_descriptor(uint8_t vector,  uint32_t* isr, uint8_t flags)
{
    struct gatedesc *desc = &idt[vector];
    
    desc->offset_low = (uint32_t)isr & 0xffff;
    desc->segment_selector = 0x08;
    desc->reserved = 0x0;
    desc->type_attributes = flags;
    desc->offset_high = (uint16_t)((uint32_t)isr >> 0x10);

}

void idt_init()
{
    idtr.base  = (uint32_t)&idt[0];
    idtr.limit = (uint16_t) sizeof(struct gatedesc) * MAX_INTS - 1;

    idt_set_descriptor(E_DIVIDE,     (uint32_t*) isr0, 0x8e);
    idt_set_descriptor(E_DEBUG,      (uint32_t*) isr1, 0x8e);
    idt_set_descriptor(E_NMI,        (uint32_t*) isr2, 0x8e);
    idt_set_descriptor(E_BREAKPOINT, (uint32_t*) isr3, 0x8e);
    idt_set_descriptor(E_OVERFLOW,   (uint32_t*) isr4, 0x8e);
    idt_set_descriptor(E_BOUND,      (uint32_t*) isr5, 0x8e); 
    idt_set_descriptor(E_INVALID_OP, (uint32_t*) isr6, 0x8e); 
    idt_set_descriptor(E_DEVICE,     (uint32_t*) isr7, 0x8e); 
    idt_set_descriptor(E_DBLFLT,     (uint32_t*) isr8, 0x8e); 
    idt_set_descriptor(9,            (uint32_t*) isr9, 0x8e); 
    idt_set_descriptor(E_TSS,        (uint32_t*) isr10, 0x8e);
    idt_set_descriptor(E_SEGNP,      (uint32_t*) isr11, 0x8e);
    idt_set_descriptor(E_SEGFAULT,   (uint32_t*) isr12, 0x8e);
    idt_set_descriptor(E_GP,         (uint32_t*) isr13, 0x8e);    
    idt_set_descriptor(E_PAGE_FAULT, (uint32_t*) isr14, 0x8e);
    idt_set_descriptor(15,           (uint32_t*) isr15, 0x8e);
    idt_set_descriptor(E_FP_ERROR,   (uint32_t*) isr16, 0x8e);
    idt_set_descriptor(E_ALGN_CHECK, (uint32_t*) isr17, 0x8e);
    idt_set_descriptor(E_MACH_CHECK, (uint32_t*) isr18, 0x8e);
    idt_set_descriptor(E_SIMD_ERR,   (uint32_t*) isr19, 0x8e);
    idt_set_descriptor(E_VIRT_ERR,   (uint32_t*) isr20, 0x8e);
    idt_set_descriptor(E_CTRL_ERR,   (uint32_t*) isr21, 0x8e);
    idt_set_descriptor(22,           (uint32_t*) isr22, 0x8e);
    idt_set_descriptor(23,           (uint32_t*) isr23, 0x8e);
    idt_set_descriptor(24,           (uint32_t*) isr24, 0x8e);
    idt_set_descriptor(25,           (uint32_t*) isr25, 0x8e);
    idt_set_descriptor(26,           (uint32_t*) isr26, 0x8e);
    idt_set_descriptor(27,           (uint32_t*) isr27, 0x8e);
    idt_set_descriptor(28,           (uint32_t*) isr28, 0x8e);
    idt_set_descriptor(29,           (uint32_t*) isr29, 0x8e);
    idt_set_descriptor(30,           (uint32_t*) isr30, 0x8e);
    idt_set_descriptor(31,           (uint32_t*) isr31, 0x8e);

    __asm__ volatile ("lidt %0": : "m"(idtr));
    __asm__ volatile ("sti");
        
}

void exception_handler()
{
    vga_print_string("EXCEPTION\n");
    __asm__ volatile("cli; hlt");
}

