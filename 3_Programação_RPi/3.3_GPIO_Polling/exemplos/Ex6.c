#include <stdio.h>
#include <unistd.h>
#include "../inc/gpiod_lib.h"

static int count = 0;
static gpio_t *g = NULL;

void on_button(unsigned int pin, int value)
{
	// Only care about falling edge (value == 0)
	if (value == 0)
	{
		count++;

		if (pin == 4)
			printf("[%d] GPIO4 pressed\n", count);
		else if (pin == 17)
			printf("[%d] GPIO17 pressed\n", count);

		// simple debounce
		usleep(200000);
	}
}

int main()
{
	unsigned int pins[] = {4, 17};

	g = gpio_open(pins, 2,
				  GPIO_INPUT,
				  GPIO_PULL_UP,
				  GPIO_EDGE_FALLING);

	if (!g) {
		puts("Erro ao configurar GPIO");
		return 1;
	}

	puts("Pressione os botoes...");

	gpio_set_callback(g, on_button);

	// Wait until 15 presses
	while (count < 15) {
		sleep(1);
	}

	gpio_close(g);

	puts("Fim!");
	return 0;
}
