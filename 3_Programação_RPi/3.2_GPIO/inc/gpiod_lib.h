#ifndef _GPIOD_LIB_H_
#define _GPIOD_LIB_H_

#include <gpiod.h>
#include <unistd.h>

void gpio_write(int offset, int value);

#endif // _GPIOD_LIB_H_
