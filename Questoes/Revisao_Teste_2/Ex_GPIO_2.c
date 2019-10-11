#include <wiringPi.h>
#include <unistd.h>
#include <signal.h>

#define SAIDA 7
#define ENTRADA 2

void sqwv(int freq_hz)
{
	int T_us_2 = (500000 + (freq_hz/2))/freq_hz;
	while(1)
        {
                digitalWrite(SAIDA, HIGH);
                usleep(T_us_2);
                digitalWrite(SAIDA, LOW);
                usleep(T_us_2);
        }
}


int main(void)
{
	int f = 1, pid_filho;
	wiringPiSetup();
	pinMode(SAIDA, OUTPUT);
	pinMode(ENTRADA, INPUT);
	while(1)
	{
		pid_filho = fork();
		if(pid_filho==0)
			sqwv(f);
		while(digitalRead(ENTRADA)>0);
		f = (f>32) ? 1 : 2*f;
		kill(pid_filho, SIGKILL);
		while(digitalRead(ENTRADA)==0);
		usleep(300000);
	}
	return 0;
}
