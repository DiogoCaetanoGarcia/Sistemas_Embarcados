// Access from ARM Running Linux
#include "../inc/gpio_dev_mem.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int ctrl_c = 0;

void funcao_para_control_c()
{
	ctrl_c = 1;
}

int main(void)
{
	int pin = 4;
	float freq, duty_cyc;
	int periodo_us;
	int periodo_alto;
	int periodo_baixo;
	signal(SIGINT, funcao_para_control_c);

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
	setup_io();
	INP_GPIO(pin);
	OUT_GPIO(pin);
	while(ctrl_c==0)
	{
		GPIO_SET = 1<<pin;
		usleep(periodo_alto);
		GPIO_CLR = 1<<pin;
		usleep(periodo_baixo);
	}
	GPIO_CLR = 1<<pin;
	return 0;
}

