#include "../inc/gpiod_lib.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	unsigned int pin = 4;
	float freq, duty_cyc;
	int periodo_us;
	int periodo_alto;
	int periodo_baixo;

	printf("Digite a frequência desejada: ");
	scanf("%f", &freq);
	if(freq<=0.0)
	{
		printf("Frequência de %f Hz inválida!\n", freq);
		return -1;
	}
	printf("Digite o ciclo de trabalho desejado (0-100): ");
	scanf("%f", &duty_cyc);
	if( (duty_cyc<0.0) || (duty_cyc>100.0) )
	{
		printf("Ciclo de trabalho de %f %% inválido!\n", duty_cyc);
		return -1;
	}
	periodo_us = (int) (1.0e6/freq);
	periodo_alto = (int) (periodo_us*duty_cyc/100);
	periodo_baixo = periodo_us - periodo_alto;
	gpio_t *led = gpio_open(&pin, 1, GPIO_OUTPUT, GPIO_BIAS_NONE, GPIO_EDGE_NONE);
	while(1)
	{
		gpio_write(led, 0, 1);
		usleep(periodo_alto);
		gpio_write(led, 0, 0);
		usleep(periodo_baixo);
	}
	return 0;
}
