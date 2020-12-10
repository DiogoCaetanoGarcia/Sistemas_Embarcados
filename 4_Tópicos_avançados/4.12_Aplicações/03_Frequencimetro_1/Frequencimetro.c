#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

// Usar GPIO Pino 27, que é Pino 2 na wiringPi
#define PINO_ENT 2
#define SEC_N        1000000000ul
#define T_AMOSTRAGEM SEC_N

unsigned long contagem_eventos;
struct timespec t[2];

void conta_eventos(void)
{
	struct timespec t_now;
	clock_gettime(CLOCK_MONOTONIC, &t_now);

	if(contagem_eventos==0)
	{
		t[0].tv_sec = t_now.tv_sec;
		t[0].tv_nsec = t_now.tv_nsec;
	}
	else
	{
		t[1].tv_sec = t_now.tv_sec;
		t[1].tv_nsec = t_now.tv_nsec;
	}
	contagem_eventos++;
}

void sleep_until(unsigned long delay)
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	while(delay >= SEC_N)
	{
		ts.tv_sec++;
		delay -= SEC_N;
	}
	ts.tv_nsec += delay;
	while(ts.tv_nsec >= SEC_N)
	{
		ts.tv_sec++;
		ts.tv_nsec -= SEC_N;
	}
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts,  NULL);
}

int main(void)
{
	double freq;
	wiringPiSetup();
	wiringPiISR(PINO_ENT, INT_EDGE_FALLING, &conta_eventos);
	while(1)
	{
		//printf("Medir freq: ENTER / Sair: CTRL-C ");
		//getchar();
		contagem_eventos = 0;
		sleep_until(T_AMOSTRAGEM);
		freq  = (double)t[1].tv_sec;
		freq -= (double)t[0].tv_sec;
		freq += ((double)t[1].tv_nsec)*1.0e-9;
		freq -= ((double)t[0].tv_nsec)*1.0e-9;
		freq /= (double)(contagem_eventos-1);
		freq = 1.0/freq;
		if(freq>=1.0e6)
			printf("Frequencia = %f MHz\n", freq*1.0e-6);
		else if(freq>=1.0e3)
			printf("Frequencia = %f kHz\n", freq*1.0e-3);
		else
			printf("Frequencia = %f Hz\n", freq);
	}
	return 0;
}
