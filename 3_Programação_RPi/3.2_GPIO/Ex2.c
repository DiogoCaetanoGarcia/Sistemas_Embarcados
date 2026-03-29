#include <stdio.h>
#include <unistd.h>
#include "inc/gpiod_lib.h"

int main()
{
	puts("Acendendo o LED.");
	gpio_write(4, 1);
	puts("Aguardando 5 segundos...");
	sleep(5);
        puts("Apagando o LED.");
	gpio_write(4, 0);
        puts("Fim.");
	return 0;
}
