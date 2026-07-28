/*
 *  This is a single header string libray for now.
 *  In the future it might make sense to add 
 *  function implementations to separate file.
 * 
*/

#ifndef STRING_H_
#define STRING_H_

#include "types.h"

static u32 strlen(const char* cstr)
{
    u32 len = 0;
    while (cstr++)
    {
        ++len;
    }
    return len;
}

#endif // STRING_H_
