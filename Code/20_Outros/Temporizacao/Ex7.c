#include <stdio.h>
#include <time.h>
#include <unistd.h>

void sleep_nsec(struct timespec ts, int delay_sec, int delay_nsec)
{		
	ts.tv_nsec += delay_nsec;
	ts.tv_sec  += delay_sec;
	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts,  NULL);
}

int main(void)
{
	unsigned int i;
	struct timespec t1, t2;
	double dummy_calc;
	long diff_ts;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	sleep_nsec(t1, 1, 0);
	clock_gettime(CLOCK_MONOTONIC, &t2);
	diff_ts = t2.tv_nsec - t1.tv_nsec;
	dummy_calc = difftime(t2.tv_sec, t1.tv_sec);
	if(dummy_calc>0.0)
			diff_ts += 1E9L;
	printf("Atraso de sleep_nsec(1s, 0ns): %f s\n",
		((float)diff_ts)/1.0E9);
}