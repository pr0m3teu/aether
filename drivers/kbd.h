#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "driver.h"

#define KBD_DATA_PORT   0x60
#define KBD_CMD_PORT    0x64
#define KBD_STATUS_PORT 0x64
#define KBD_STATUS_OUTPUT_FULL  0x01


#define K_RELEASE 0x80

#define MAX_KBD_BUF 256 // defined as uint8_t max so we can use 2 uint8_t var as indexes

static const unsigned char ascii_map[0x60] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8',       // 0x0  - 0x9
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',  // 0x0a - 0x13
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,     // 0x14 - 0x1d
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',    // 0x1e - 0x27
    '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n',    // 0x28 - 0x31
    'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0             // 0x32 - -x3b
};


void kbd_init(void);
void kbd_irq_handle(void);
int8_t kbd_get_char(void);

extern struct driver_ops kbd_ops;

#endif // KEYBOARD_H_


