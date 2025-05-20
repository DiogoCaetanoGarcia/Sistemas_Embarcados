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
	wiringPiSetup();
	pinMode(pin_sg90, OUTPUT);

	while(1)
	{
		printf("Digite um ângulo entre -90 e 90 graus: ");
		scanf("%f", &angulo);
		if(pid_filho != 0)
			kill(pid_filho, SIGKILL);
		pid_filho = fork();
		if(pid_filho==0)
			posiciona_SG90(angulo, pin_sg90);
	}
	return 0;
}
