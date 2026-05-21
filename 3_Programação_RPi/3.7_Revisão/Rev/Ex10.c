#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "gpiod_lib.h"

void posiciona_SG90(float angulo, gpio_t* pin)
{
	int high_us = (int)(angulo*50.0/9.0 + 1500);
	int low_us  = 20000 - high_us;
	while(1)
	{
		gpio_write(pin, 0, 1);
		usleep(high_us);
		gpio_write(pin, 0, 0);
		usleep(low_us);
	}
}

int main(void)
{
	int pin_sg90 = 17;
	float angulo;
	int pid_filho = 0;
	float angulos[] = {-90, -67.5, -45, -22.5, 0, 22.5, 45, 67.5, 90, 67.5, 45, 22.5, 0, -22.5, -45, -67.5};
	int cont = 0;
	gpio_t *sg90 = gpio_open(&pin_sg90, 1, GPIO_OUTPUT, GPIO_BIAS_NONE, GPIO_EDGE_NONE);

	while(1)
	{
		angulo = angulos[cont];
		cont = (cont+1)%16;
		if(pid_filho != 0)
			kill(pid_filho, SIGKILL);
		pid_filho = fork();
		if(pid_filho==0)
			posiciona_SG90(angulo, sg90);
		usleep(125000);
	}
	return 0;
}

/*
#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void posiciona_SG90(float angulo, int pin_out)
{
	int high_us = (int)(angulo*50.0/9.0 + 1500);
	int low_us  = 20000 - high_us;
	while(1)
	{
		digitalWrite(pin_out, HIGH);
		usleep(high_us);
		digitalWrite(pin_out, LOW);
		usleep(low_us);
	}
}

int main(void)
{
	int pin_sg90 = 0;
	float angulo;
	int pid_filho = 0;
	float angulos[] = {-90, -67.5, -45, -22.5, 0, 22.5, 45, 67.5, 90, 67.5, 45, 22.5, 0, -22.5, -45, -67.5};
	int cont = 0;
	wiringPiSetup();
	pinMode(pin_sg90, OUTPUT);

	while(1)
	{
		angulo = angulos[cont];
		cont = (cont+1)%16;
		if(pid_filho != 0)
			kill(pid_filho, SIGKILL);
		pid_filho = fork();
		if(pid_filho==0)
			posiciona_SG90(angulo, pin_sg90);
		usleep(125000);
	}
	return 0;
}
*/
