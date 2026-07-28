#include "driver.h"


void drivers_init(struct driver_ops **drivers)
{
    for (int i = 0; drivers[i]; ++i)
    {
        if (drivers[i]->init) drivers[i]->init();
    }
}

