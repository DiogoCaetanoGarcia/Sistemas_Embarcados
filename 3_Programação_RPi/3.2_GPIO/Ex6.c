 // Access from ARM Running Linux
#include "gpio_dev_mem.h"

//Compile junto com o arquivo gpio_dev_mem.c
int main(int argc, char **argv)
{
	int i = 0;
	// Set up gpi pointer for direct register access
	setup_io();
	INP_GPIO(4);
	GPIO_PULL = 1<<4;
	while(i<15)
	{
		printf("i = %d\n", i);
		puts("Pressione o botao");
		while(GET_GPIO(4));
		puts("Botao pressionado");
		while(GET_GPIO(4)==0);
		puts("Botao solto");
		i++;
	}
	return 0;
}
