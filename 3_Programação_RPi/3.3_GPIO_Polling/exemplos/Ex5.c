#include <stdio.h>
#include <unistd.h>
#include "../inc/gpiod_lib.h"

int main()
{
	unsigned int pins[] = {4, 17}, N_pins = 2;
	unsigned int events[4], N_events = 4;

	gpio_t *g = gpio_open(pins, N_pins, GPIO_INPUT, GPIO_PULL_UP, GPIO_EDGE_FALLING);

	for (int i=0; i<5; i++)
	{
		int n = gpio_poll(g, -1, events, N_events);
		for (int j=0; j<n; j++)
		{
			for(int k=0; k<N_pins; k++)
			{
				if (events[j] == pins[k])
				{
					printf("GPIO%d!\n", pins[k]);
					while(gpio_read(g, pins[k])==0);
					usleep(300000);
					gpio_flush_events(g);
					break;
				}
			}
		}
	}
}
