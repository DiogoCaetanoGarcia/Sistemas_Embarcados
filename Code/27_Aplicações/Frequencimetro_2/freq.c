#include "freq.h"

struct freq_calc fc;

void config_freq(void)
{
	wiringPiSetup();
	wiringPiISR(PINO_ENT, INT_EDGE_FALLING, &conta_eventos);
	Config_Pins();
	Config_LCD();
}

void conta_eventos(void)
{
	struct timespec t_now;
	clock_gettime(CLOCK_MONOTONIC, &t_now);

	if(fc.contagem_eventos==0)
	{
		fc.t[0].tv_sec = t_now.tv_sec;
		fc.t[0].tv_nsec = t_now.tv_nsec;
	}
	else
	{
		fc.t[1].tv_sec = t_now.tv_sec;
		fc.t[1].tv_nsec = t_now.tv_nsec;
	}
	fc.contagem_eventos++;
}

void sleep_until(unsigned long delay)
{
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	while(delay >= 1000000000ul)
	{
		ts.tv_sec++;
		delay -= 1000000000ul;
	}
	ts.tv_nsec += delay;
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts,  NULL);
}

void calc_freq(void)
{
	double freq;
	char str[80];
	while(1)
	{
		fc.contagem_eventos = 0;
		sleep_until(T_AMOSTRAGEM);
		freq  = (double)fc.t[1].tv_sec;
		freq -= (double)fc.t[0].tv_sec;
		freq += ((double)fc.t[1].tv_nsec)*1.0e-9;
		freq -= ((double)fc.t[0].tv_nsec)*1.0e-9;
		freq /= (double)(fc.contagem_eventos-1);
		freq = 1.0/freq;
		Clear_LCD();
		Send_String("F = ");
		if(freq>=1.0e6)
		{
			//sprintf(str, "F = %f MHz", freq*1.0e-6);
			Send_Double(freq*1.0e-6, 6);
			Send_String("MHz");
		}
		else if(freq>=1.0e3)
		{
			//sprintf(str, "F = %f kHz", freq*1.0e-3);
			Send_Double(freq*1.0e-3, 6);
			Send_String("kHz");
		}
		else
		{
			//sprintf(str, "F = %f Hz", freq);
			Send_Double(freq, 6);
			Send_String("Hz");
		}
		//Send_String(str);
	}
}
