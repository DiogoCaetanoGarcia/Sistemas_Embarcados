#include <wiringPi.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define SAIDA 7
#define ENTRADA 2
#define MAX_MEIO_PERIODO (1e6/2)
#define MIN_MEIO_PERIODO (1e6/64)

int meio_periodo = MAX_MEIO_PERIODO;

void muda_freq()
{
	meio_periodo /= 2;
	if(meio_periodo<MIN_MEIO_PERIODO)
		meio_periodo = MAX_MEIO_PERIODO;
}

int main(void)
{
	pid_t filho;
	wiringPiSetup();
	pinMode(SAIDA, OUTPUT);
	pinMode(ENTRADA, INPUT);
	pullUpDnControl(ENTRADA, PUD_UP);
	signal(SIGUSR1, muda_freq);
	filho = fork();
	if(filho==0)
	{
		while(1)
		{
			digitalWrite(SAIDA, HIGH);
			usleep(meio_periodo);
			digitalWrite(SAIDA, LOW);
			usleep(meio_periodo);
		}
	}
	else
	{
		while(1)
		{
			while(digitalRead(ENTRADA)>0);
			kill(filho,SIGUSR1);
			while(digitalRead(ENTRADA)==0);
			usleep(300000);
		}
	}
}