#ifndef UTIL_H_
#define UTIL_H_

void kclear(void);
void kprint(const char* cstr);
void kpanic(const char* cstr) __attribute__((noreturn));

void kassert(_Bool cond, const char* cstr);


#endif // UTIL_H_

