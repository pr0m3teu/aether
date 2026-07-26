#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "common/types.h"
#include "x86.h"

#define MAX_INTS 256

// CPU defined exceptions 
#define E_DIVIDE      0   // Divide Error
#define E_DEBUG       1   // Debug Exception
#define E_NMI         2   // NMI Interrupt
#define E_BREAKPOINT  3   // Breakpoint
#define E_OVERFLOW    4   // Overflow
#define E_BOUND       5   // BOUND Range Exceeded
#define E_INVALID_OP  6   // Invalid Opcode (Undefined Opcode)
#define E_DEVICE      7   // Device Not Available (No Math Coprocessor)
#define E_DBLFLT      8   // Double Fault
// RESERVED           9   // Coprocessor Segment Overrun (reserved)
#define E_TSS         10  // Invalid TSS
#define E_SEGNP       11  // Segment Not Present
#define E_SEGFAULT    12  // Stack-Segment Fault
#define E_GP          13  // General Protection 
#define E_PAGE_FAULT  14  // Page Fault 
// RESERVED           15  
#define E_FP_ERROR    16  // x87 FPU Floating-Point Error (Math Fault)
#define E_ALGN_CHECK  17  // Alignment Check 
#define E_MACH_CHECK  18  // Machine Check
#define E_SIMD_ERR    19  // SIMD Floating-Point Exception
#define E_VIRT_ERR    20  // Virtualization Exception
#define E_CTRL_ERR    21  // Control Protection Exception


// 32-bit only 
struct gatedesc {
    uint16_t offset_low;
    uint16_t segment_selector;

    uint8_t  reserved;
    uint8_t  type_attributes;
    
    uint16_t offset_high;
} __attribute__((packed));


struct idtr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


void exception_handler(struct trapframe *tr) __attribute__((noreturn));

void idt_init(void);

// Exception routines
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif // INTERRUPTS_H_
