#include <stdio.h>
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
