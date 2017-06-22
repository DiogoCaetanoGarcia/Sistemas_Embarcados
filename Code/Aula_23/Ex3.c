#include "rt_lib.h"

int main(void)
{
	struct sched_param sp;
	struct timespec ts;
	unsigned int logindex=0;
	int val = 0;
	pin0 = init_gpio(PIN_VALUE);
	signal(SIGINT, dumptimestamps);
	clock_gettime(CLOCK_MONOTONIC, &ts);

	sp.sched_priority = 99;
	if(pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp))
	{
		fprintf(stderr,"WARNING: Failed to set stepper thread"
			"to real-time priority\n");
	}

	while(1)
	{
		sleep_until(&ts, DELAY_NS);
		logtimestamp(&t[logindex]);
		setiopin(pin0,val);
		INC_CNT(logindex, MAX_LOGENTRIES);
		INC_CNT(val, 2);
	}
}
