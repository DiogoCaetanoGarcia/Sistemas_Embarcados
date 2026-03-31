#include <stdio.h>
#include "../inc/gpiod_lib.h"

int main(void)
{
	int i = 0;
	unsigned int pin = 4;
	gpio_t *btn = gpio_open(&pin, 1, GPIO_INPUT, GPIO_PULL_UP, GPIO_EDGE_NONE);
	while(i<15)
	{
		printf("i = %d\n", i);
		puts("Pressione o botao");
		while(gpio_read(btn, 0));
		puts("Botao pressionado");
		while(gpio_read(btn, 0)==0);
		puts("Botao solto");
		i++;
	}
	return 0;
}
