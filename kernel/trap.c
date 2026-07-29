#include "common/kassert.h"
#include "common/util.h"
#include "drivers/kbd.h"

#include "pic.h"
#include "interrupts.h"


void trap(const struct trapframe *tf)
{
    KASSERT(tf);
    KASSERT(tf->trapno > 0x01f);
    KASSERT(tf->trapno < 0x100);
    
    switch(tf->trapno)
    {
        case (TRAP | IRQ_KBD):
            kbd_irq_handle();
            pic_eoi(IRQ_KBD);
            break;
        default:
            kpanic("(trap) Unknown interrupt\n");
    }
}


