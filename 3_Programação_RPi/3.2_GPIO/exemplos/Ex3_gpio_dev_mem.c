// Access from ARM Running Linux
#include "../inc/gpio_dev_mem.h"

//Compile junto com o arquivo gpio_dev_mem.c
int main(int argc, char **argv)
{
	int i = 0, pin = 17;
	// Set up gpi pointer for direct register access
	setup_io();
	INP_GPIO(pin);
	while(i<15)
	{
		printf("i = %d\n", i);
		puts("Pressione o botao");
		while(GET_GPIO(pin));
		puts("Botao pressionado");
		while(GET_GPIO(pin)==0);
		puts("Botao solto");
		i++;
	}
	return 0;
}
