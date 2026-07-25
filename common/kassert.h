#ifndef KASSERT_H_
#define KASSERT_H_

#include "types.h"

void kassert_fail(const char* cond, const char* file, uint32_t line) __attribute__((noreturn));

#define KASSERT(cond) \
    do {      \
        if(!(cond))                  \
        {                            \
            kassert_fail(#cond, __FILE__, __LINE__);\
        }                            \
    } while(0);                      \


#endif // KASSERT_H_
