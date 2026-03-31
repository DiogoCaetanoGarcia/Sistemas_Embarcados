#include <stdio.h>
#include <unistd.h>
#include "../inc/gpiod_lib.h"

int main()
{
	int pin = 4, btn_press, res;
	gpio_t *btn = gpio_open(pin, GPIO_INPUT, GPIO_BIAS_NONE, GPIO_EDGE_FALLING);
	puts("Pressione o botão...");
	for(btn_press=0; btn_press<5; btn_press++)
	{
		res = gpio_poll(btn, -1);
		puts("Borda de descida!");
		while(gpio_read(btn)==0);
		usleep(300000);
		gpio_flush_events(btn);
	}
	gpio_close(btn);
	return 0;
}
