#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "gpiod_lib.h"

int main(void)
{
	int meio_periodo = 500000;
	int pin_btn = 4, pin_led = 17;
	int pid_filho;
	gpio_t *led = gpio_open(&pin_led, 1, GPIO_OUTPUT, GPIO_BIAS_NONE, GPIO_EDGE_NONE);
	gpio_t *btn = gpio_open(&pin_btn, 1, GPIO_INPUT,  GPIO_BIAS_NONE, GPIO_EDGE_NONE);

	while(1)
	{
		printf("Freq = %d Hz\n", 1000000/2/meio_periodo);
		pid_filho = fork();
		if(pid_filho==0)
		{
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
			while(gpio_read(btn, 0)==1);
			while(gpio_read(btn, 0)==0);
			usleep(300000);
			meio_periodo /= 2;
			if(meio_periodo < 7812)
				meio_periodo = 500000;
			kill(pid_filho, SIGKILL);
		}
	}
}

/*#include <stdio.h>
#include <wiringPi.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	int pin_btn = 7, pin_led = 0;
	int meio_periodo = 500000;
	int pid_filho;
	wiringPiSetup();
	pinMode(pin_btn, INPUT);
	pinMode(pin_led, OUTPUT);

	while(1)
	{
		printf("Freq = %d Hz\n", 1000000/2/meio_periodo);
		pid_filho = fork();
		if(pid_filho==0)
		{
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
			while(digitalRead(pin_btn)==1);
			while(digitalRead(pin_btn)==0);
			usleep(300000);
			meio_periodo /= 2;
			if(meio_periodo < 7812)
				meio_periodo = 500000;
			kill(pid_filho, SIGKILL);
		}
	}
}
*/
