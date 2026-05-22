#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int pin = 7;
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
	wiringPiSetup();
	pinMode(pin, OUTPUT);
	while(1)
	{
		digitalWrite(pin, HIGH);
		usleep(periodo_alto);
		digitalWrite(pin, LOW);
		usleep(periodo_baixo);
	}
	return 0;
}

