#include "arch/x86.h"
#include "common/util.h"
#include "common/kassert.h"
#include "common/types.h"
#include "driver.h"
#include "kbd.h"

extern void consoleintr(char (*getc)(void));

static char kbd_buf[MAX_KBD_BUF] = {0};
static uint8_t head = 0;
static uint8_t tail = 0;

static inline void kbd_wait_input(void)
{
    while (inb(KBD_STATUS_PORT) & 0x2);
}

static void kbd_wait_output(void) {
    while (!(inb(KBD_STATUS_PORT) & KBD_STATUS_OUTPUT_FULL));
}

void kbd_init()
{
    kbd_wait_input();
    outb(KBD_CMD_PORT, 0xAE); // enable first PS/2 port (keyboard)

    // Flush anything sitting in the output buffer from boot.
    while (inb(KBD_STATUS_PORT) & KBD_STATUS_OUTPUT_FULL) {
        (void)inb(KBD_DATA_PORT);
    }

    kbd_wait_input();
    outb(KBD_DATA_PORT, 0xff); // Reset
    kbd_wait_output();

    uint8_t status = inb(KBD_DATA_PORT);

    if (status != 0xFA && status != 0xFE) // ACK
    {
        kprint_hex(status);
        kpanic("(kbd_init) 0xFA");
    }

    kbd_wait_output();
    if (inb(KBD_DATA_PORT) != 0xAA) // Self-test passed
        kpanic("(kbd_init) 0xAA");

}

static char kbd_get_char(void)
{
    KASSERT(head <= tail);

    if (head == tail) return -1;

    char c = kbd_buf[head++];    
    if (head == UINT8_MAX) head = 0;

    return c;
}

void kbd_irq_handle()
{
    KASSERT(head <= tail);
    uint8_t scancode = inb(KBD_DATA_PORT);
    uint8_t release  = scancode & K_RELEASE;

    scancode &= 0x7f;
    if (release) return;

    uint8_t key = ascii_map[scancode];
    if (key)
    {
        kbd_buf[tail++] = key;
        if (tail == UINT8_MAX )
        {
            tail = 0;
        }
    }

    consoleintr(&kbd_get_char);
}


struct driver_ops kbd_ops = {
    .name = "PS/2 Keyboard driver",
    .init = &kbd_init,
    .write = 0,
    .read  = 0,
};


