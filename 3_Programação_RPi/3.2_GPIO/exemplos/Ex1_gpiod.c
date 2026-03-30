#include <stdio.h>
#include <unistd.h>
#include "../inc/gpiod_lib.h"

int main()
{
	int pin = 4;
	puts("Acendendo o LED.");
	gpio_t *led = gpio_open(pin, GPIO_OUTPUT, GPIO_BIAS_NONE, GPIO_EDGE_NONE);
	gpio_write(led, 1);
	puts("Aguardando 5 segundos...");
	sleep(5);
        puts("Apagando o LED.");
	gpio_write(led, 0);
        puts("Fim.");
	gpio_close(led);
	return 0;
}
