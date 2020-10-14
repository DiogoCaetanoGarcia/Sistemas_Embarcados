 // Access from ARM Running Linux
#include "gpio_dev_mem.h"

//Compile junto com o arquivo gpio_dev_mem.c
int main(int argc, char **argv)
{
	// Set up gpi pointer for direct register access
	setup_io();
	INP_GPIO(4);
	while(1)
	{
		puts("Pressione o botao");
		while(GET_GPIO(4));
		puts("Botao pressionado");
		while(GET_GPIO(4)==0);
		puts("Botao solto");
	}
	return 0;
}
