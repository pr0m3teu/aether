#ifndef SERIAL_H_
#define SERIAL_H_

#include "driver.h"
#include "common/types.h"
#define COM1 0x3f8

void serial_init(void);
void serial_putc(char c);
void serial_print_string(const char* cstr);
void serial_print_uint(uint32_t num);
uint32_t serial_write(const uint8_t* buf, uint32_t len);

extern struct driver_ops serial_ops;

#endif // SERIAL_H_
