#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "kernel/types.h"

#define MAX_INTS 256

// Processor defined interrupts
#define T_DIVIDE      0   // Divide Error
#define T_DEBUG       1   // Debug Exception
#define T_NMI         2   // NMI Interrupt
#define T_BREAKPOINT  3   // Breakpoint
#define T_OVERFLOW    4   // Overflow
#define T_BOUND       5   // BOUND Range Exceeded
#define T_INVALID_OP  6   // Invalid Opcode (Undefined Opcode)
#define T_DEVICE      7   // Device Not Available (No Math Coprocessor)
#define T_DBLFLT      8   // Double Fault
// RESERVED           9   // Coprocessor Segment Overrun (reserved)
#define T_TSS         10  // Invalid TSS
#define T_SEGNP       11  // Segment Not Present
#define T_SEGFAULT    12  // Stack-Segment Fault
#define T_GP          13  // General Protection 
#define T_PAGE_FAULT  14  // Page Fault 
// RESERVED           15  
#define T_FP_ERROR    16  // x87 FPU Floating-Point Error (Math Fault)
#define T_ALGN_CHECK  17  // Alignment Check 
#define T_MACH_CHECK  18  // Machine Check
#define T_SIMD_ERR    19  // SIMD Floating-Point Exception
#define T_VIRT_ERR    20  // Virtualization Exception
#define T_CTRL_ERR    21  // Control Protection Exception
                          


// 32-bit only 
struct gatedesc {
    uint16_t offset_low;
    uint16_t segment_selector;

    uint8_t  reserved;
    uint8_t  type_attributes;
    
    uint16_t offset_high;
} __attribute__((packed));


struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


__attribute__((aligned(0x10))) struct gatedesc idt[MAX_INTS];


__attribute__((noreturn)) void exception_handler(void);


#endif // INTERRUPTS_H_
