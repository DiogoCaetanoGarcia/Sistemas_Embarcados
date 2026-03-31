#include <stdio.h>
#include "../inc/gpiod_lib.h"

int main()
{
	int pin = 4, btn_press;
	gpio_t *btn = gpio_open(pin, GPIO_INPUT, GPIO_BIAS_NONE, GPIO_EDGE_FALLING);
	puts("Pressione o botão...");
	for(btn_press=0; btn_press<5; btn_press++)
	{
		gpio_poll(btn, -1);
		puts("Borda de descida!");
	}
	gpio_close(btn);
	return 0;
}
