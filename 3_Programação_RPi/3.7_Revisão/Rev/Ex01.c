#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "gpiod_lib.h"

int meio_periodo = 500000;

void f_sigusr1(int i)
{
	meio_periodo /= 2;
	if(meio_periodo < 7812)
		meio_periodo = 500000;
	printf("Freq = %d Hz\n", 1000000/2/meio_periodo);
}

int main(void)
{
	int pin_btn = 4, pin_led = 17;
	gpio_t *led = gpio_open(&pin_led, 1, GPIO_OUTPUT, GPIO_BIAS_NONE, GPIO_EDGE_NONE);
	gpio_t *btn = gpio_open(&pin_btn, 1, GPIO_INPUT,  GPIO_BIAS_NONE, GPIO_EDGE_NONE);
	int pid_filho;

	pid_filho = fork();
	if(pid_filho==0)
	{
		signal(SIGUSR1, f_sigusr1);
		printf("Freq = %d Hz\n", 1000000/2/meio_periodo);
		while(1)
		{
			gpio_write(led, 0, 1);
			usleep(meio_periodo);
			gpio_write(led, 0, 0);
			usleep(meio_periodo);
		}
	}
	else
	{
		while(1)
		{
			while(gpio_read(btn, 0)==1);
			while(gpio_read(btn, 0)==0);
			usleep(300000);
			kill(pid_filho, SIGUSR1);
		}
	}
}

/*
#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

int meio_periodo = 500000;

void f_sigusr1(int i)
{
	meio_periodo /= 2;
	if(meio_periodo < 7812)
		meio_periodo = 500000;
	printf("Freq = %d Hz\n", 1000000/2/meio_periodo);
}

int main(void)
{
	int pin_btn = 7, pin_led = 0;
	int pid_filho;
	wiringPiSetup();
	pinMode(pin_btn, INPUT);
	pinMode(pin_led, OUTPUT);

	pid_filho = fork();
	if(pid_filho==0)
	{
		signal(SIGUSR1, f_sigusr1);
		while(1)
		{
			digitalWrite(pin_led, HIGH);
			usleep(meio_periodo);
			digitalWrite(pin_led, LOW);
			usleep(meio_periodo);
		}
	}
	else
	{
		while(1)
		{
			while(digitalRead(pin_btn)==1);
			while(digitalRead(pin_btn)==0);
			usleep(300000);
			kill(pid_filho, SIGUSR1);
		}
	}
}
*/
