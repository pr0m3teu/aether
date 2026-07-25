#ifndef SERIAL_H_
#define SERIAL_H_

#define COM1 0x3f8

void serial_init(void);
void serial_write(char c);
void serial_print(const char* cstr);

#endif // SERIAL_H_
