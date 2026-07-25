#include "kassert.h"
#include "util.h"
#include "drivers/serial.h"

void kassert_fail(const char* cond, const char* file, uint32_t line)
{
    serial_print_string("\n[ASSERTION FAILED] ");
    serial_print_string(cond);
    serial_print_string("\n");
    serial_print_string("at ");
    serial_print_string(file);
    serial_print_string(":");
    serial_print_uint(line);
    serial_print_string("\n");

    kpanic("Assertion failed! (see serial output)");
}
