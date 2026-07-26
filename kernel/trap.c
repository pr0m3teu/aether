#include "common/kassert.h"
#include "common/util.h"

#include "pic.h"
#include "interrupts.h"

void trap(const struct trapframe *tf)
{
    KASSERT(tf);
    KASSERT(tf->trapno > 0x1f);
    
    switch(tf->trapno)
    {
        case (TRAP | IRQ_KBD):
            pic_eoi(IRQ_KBD);
            break;
        default:
            kpanic("(trap) Unknown interrupt\n");

    }
    
}
