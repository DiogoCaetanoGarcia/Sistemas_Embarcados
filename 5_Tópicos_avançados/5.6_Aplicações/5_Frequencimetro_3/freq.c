#include "freq.h"

struct freq_calc fc;

void config_freq(void)
{
	gpioInitialise();
	gpioSetAlertFunc(PINO_ENT, conta_eventos);
	Config_Pins();
	Config_LCD();
}

void conta_eventos(int gpio, int level, uint32_t tick)
{
	struct timespec t_now;
	if((gpio==PINO_ENT)&&(level==0))
	{
		clock_gettime(CLOCK_MONOTONIC, &t_now);
		if(fc.contagem_eventos==0)
		{
			fc.t[0].tv_sec  = t_now.tv_sec;
			fc.t[0].tv_nsec = t_now.tv_nsec;
		}
		else
		{
			fc.t[1].tv_sec  = t_now.tv_sec;
			fc.t[1].tv_nsec = t_now.tv_nsec;
		}
		fc.contagem_eventos++;
	}
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
