 // Access from ARM Running Linux
#include "inc/gpio_dev_mem.h"

//Compile junto com o arquivo gpio_dev_mem.c
int main(int argc, char **argv)
{
	int pin = 17;
	// Set up gpi pointer for direct register access
	setup_io();
	INP_GPIO(pin);
	puts("Pressione o botao");
	while(GET_GPIO(pin));
	return 0;
}
