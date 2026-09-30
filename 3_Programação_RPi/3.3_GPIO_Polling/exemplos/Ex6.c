#include <stdio.h>
#include <unistd.h>
#include "../inc/gpiod_lib.h"

#define Nbtns 2
static int count = 0;
static gpio_t *g = NULL;
unsigned int pins[] = {4, 17};

void on_button(unsigned int pin, int value)
{
	// Only care about falling edge (value == 0)
	if(value == 0)
	{
		count++;
		for(int k=0; k<Nbtns; k++)
		{
			if(pin == pins[k])
			{
				printf("[%d] GPIO%d pressed\n", count, pin);
				// Wait for user to release button
				while(gpio_read(g, k)==0);
				// simple debounce
				usleep(200000);
				gpio_flush_events(g);
			}
		}
	}
}

int main()
{
	g = gpio_open(pins, Nbtns, GPIO_INPUT, GPIO_PULL_UP, GPIO_EDGE_FALLING);
	if (!g)
	{
		puts("Erro ao configurar GPIO");
		return 1;
	}
	puts("Pressione os botoes...");
	gpio_set_callback(g, on_button);
	// Wait until 15 presses
	while (count < 15)
	{
		sleep(1);
	}
	gpio_close(g);
	return 0;
}
