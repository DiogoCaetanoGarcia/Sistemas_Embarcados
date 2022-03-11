#include <stdio.h>
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
