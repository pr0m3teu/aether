#ifndef KASSERT_H_
#define KASSERT_H_

void kassert_fail(const char* cond, const char* file) __attribute__((noreturn));

#define KASSERT(cond) \
    do {      \
        if(!(cond))                  \
        {                            \
            kassert_fail(#cond, __FILE__);\
        }                            \
    } while(0);                      \


#endif // KASSERT_H_
