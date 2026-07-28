#ifndef DRIVER_H_
#define DRIVER_H_

#include "common/types.h"

struct driver_ops {
    const char* name;
    void (*init)(void);
    uint32_t (*read) (uint8_t* buf, uint32_t len);
    uint32_t (*write)(const uint8_t* buf, uint32_t len);
};


void drivers_init(struct driver_ops **drivers);

#endif // DRIVER_H_
