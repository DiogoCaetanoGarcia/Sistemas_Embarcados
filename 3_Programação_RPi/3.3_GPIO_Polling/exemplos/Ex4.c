#include <stdio.h>
#include <unistd.h>
#include "../inc/gpiod_lib.h"

void poll_btn(gpio_t *btn);

int main()
{
	int pin = 4, btn_press;
	gpio_t *btn = gpio_open(pin, GPIO_INPUT, GPIO_BIAS_NONE, GPIO_EDGE_BOTH);
	puts("Pressione o botão...");
	for(btn_press=0; btn_press<5; btn_press++)
	{
		poll_btn(btn);
		puts("Borda de descida!");
		poll_btn(btn);
		puts("Borda de subida!");
	}
	gpio_close(btn);
	return 0;
}

#define N 1000
#define Nlim (N*2)/4

void poll_btn(gpio_t *btn)
{
	char buffer, vals[N] = {0}, res;
	int pos = 0, test=1, i, s;
	buffer = gpio_read(btn);
	for(i=0;i<N;i++)
		vals[i] = buffer;
	res = gpio_poll(btn, -1);
	while(test)
	{
		vals[pos] = gpio_read(btn);
		pos = (pos+1)%N;
		for(s=i=0; i<N; i++)
			s += vals[i];
		if(buffer==0)
			test = s<Nlim;
		else
			test = s>Nlim;
	}
	gpio_flush_events(btn);
}
