#include "rt_lib.h"

int main(void)
{
	unsigned int logindex=0;
	int val = 0;
	pin0 = init_gpio(PIN_VALUE);
	signal(SIGINT, dumptimestamps);
	while(1)
	{
		usleep(DELAY_US);
		logtimestamp(&t[logindex]);
		setiopin(pin0,val);
		INC_CNT(logindex, MAX_LOGENTRIES);
		INC_CNT(val, 2);
	}
}
