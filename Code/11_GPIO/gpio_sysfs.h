#ifndef _GPIO_SYSFS_H_
#define _GPIO_SYSFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GPIO_PATH "/sys/class/gpio"
int write_to_file(char *file_name, char *content);
int read_from_file(char *file_name, char *content, int N);
int setGPIOdirection(int pin, char *direction);
int GPIOwrite(int pin, int value);
int GPIOread(int pin);
int unsetGPIO(int pin);

#endif //_GPIO_SYSFS_H_
