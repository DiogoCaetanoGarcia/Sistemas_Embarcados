#include "rt_lib.h"

void logtimestamp(struct timespec *log_t)
{
	clock_gettime(CLOCK_MONOTONIC, log_t);
}

void panic(char *message)
{
	fprintf(stderr,"Fatal error: %s\n", message);
	exit(1);
}

void init_gpio(int gpioport)
{
	wiringPiSetup();
	pinMode(gpioport, OUTPUT);
	digitalWrite(gpioport, LOW);
}

void setiopin(int gpioport, int val)
{
	if(val==0)
		digitalWrite(gpioport, LOW);
	if(val==1)
		digitalWrite(gpioport, HIGH);
}

void end_gpio(int gpioport)
{
	digitalWrite(gpioport, LOW);
}

void sleep_until(struct timespec *ts, int delay)
{
	ts->tv_nsec += delay;
	if(ts->tv_nsec >= 1000*1000*1000)
	{
		ts->tv_nsec -= 1000*1000*1000;
		ts->tv_sec++;
	}
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, ts,  NULL);
}

void dumptimestamps(struct timespec *t)
{
	long diff_ts[MAX_LOGENTRIES];
	double mean = 0.0, std = 0.0, dummy_calc;
	int i;
	for(i=1; i < MAX_LOGENTRIES; i++)
	{
		dummy_calc = difftime(t[i].tv_sec, t[i-1].tv_sec);
		diff_ts[i-1] = t[i].tv_nsec - t[i-1].tv_nsec;
		if(dummy_calc>0.0)
			diff_ts[i-1] += 1000*1000*1000;
		mean += (double)diff_ts[i-1];
	}
	mean /= (double)(MAX_LOGENTRIES-1);
	for(i=0; i < MAX_LOGENTRIES-1; i++)
	{
		dummy_calc = (double)diff_ts[i];
		dummy_calc -= mean;
		std += dummy_calc*dummy_calc;
	}
	std /= (double)(MAX_LOGENTRIES-1);
	std = sqrt(std);
	fprintf(stderr, "\n\nEstatisticas dos timestamps:\n\n");
	fprintf(stderr, "   Media         = %2.6f ms\n",mean*1.0e-6);
	fprintf(stderr, "   Desvio-padrao = %2.6f ms\n\n",std*1.0e-6);
}
