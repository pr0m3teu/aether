#ifndef UTIL_H_
#define UTIL_H_

#include "types.h"

void kclear(void);
void kputc(char c);
void kprint(const char* cstr);
void kprint_uint(uint32_t num);
void kpanic(const char* cstr) __attribute__((noreturn));


#endif // UTIL_H_
       

