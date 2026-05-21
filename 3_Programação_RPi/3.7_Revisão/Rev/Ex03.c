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
	gpio_t *btn = gpio_open(&pin_btn, 1, GPIO_INPUT,  GPIO_BIAS_NONE, GPIO_EDGE_FALLING);

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
			gpio_poll(btn, -1, NULL, 0);
			while(gpio_read(btn, 0)==0);
			usleep(300000);
			gpio_flush_events(btn);
			meio_periodo /= 2;
			if(meio_periodo < 7812)
				meio_periodo = 500000;
			kill(pid_filho, SIGKILL);
		}
	}
}


/*#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/poll.h>

struct pollfd pfd;
int pin_led = 0;

void f_ctrlc(int i)
{
	close(pfd.fd);
	system("echo 4 > /sys/class/gpio/unexport");
	digitalWrite(pin_led, LOW);
	exit(0);
}

int main(void)
{
	int meio_periodo = 500000;
	int pid_filho;
	char buffer;

	wiringPiSetup();
	pinMode(pin_led, OUTPUT);
	system("echo 4       > /sys/class/gpio/export");
	system("echo falling > /sys/class/gpio/gpio4/edge");
	system("echo in      > /sys/class/gpio/gpio4/direction");
	pfd.fd = open("/sys/class/gpio/gpio4/value", O_RDONLY);
	pfd.events = POLLPRI | POLLERR;
	pfd.revents = 0;
	signal(SIGINT, f_ctrlc);
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
			lseek(pfd.fd, 0, SEEK_SET);
			read(pfd.fd, &buffer, 1);
			poll(&pfd, 1, -1);
			do
			{
				lseek(pfd.fd, 0, SEEK_SET);
				read(pfd.fd, &buffer, 1);
			}while(buffer=='0');
			usleep(300000);
			meio_periodo /= 2;
			if(meio_periodo < 7812)
				meio_periodo = 500000;
			kill(pid_filho, SIGKILL);
		}
	}
}
*/
