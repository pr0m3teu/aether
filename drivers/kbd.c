#include "arch/x86.h"
#include "common/util.h"
#include "common/types.h"
#include "kbd.h"

void kbdintr()
{
    uint8_t scancode = inb(0x60);
    if (scancode & K_RELEASE)
    {
        kprint("KEYBOARD RELEASED\n");
    }
    else {
        kprint("KEYBOARD PRESSED\n");
    }
}
