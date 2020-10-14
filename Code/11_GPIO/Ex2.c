#include "gpio_sysfs.h"
#include <unistd.h>

int main()
{
	int pin=4;
	if(setGPIOdirection(pin, "out"))
		return -1;
	if(GPIOwrite(pin, 1))
		return -2;
	sleep(5);
	if(unsetGPIO(pin))
		return -3;
	return 0;
}
