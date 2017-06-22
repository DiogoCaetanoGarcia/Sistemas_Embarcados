#include "rt_lib.h"

struct timespec t[MAX_LOGENTRIES];
FILE *pin0;

void logtimestamp(struct timespec *log_t)
{
	clock_gettime(CLOCK_MONOTONIC, log_t);
}

void panic(char *message)
{
	fprintf(stderr,"Fatal error: %s\n", message);
	exit(1);
}

FILE *init_gpio(int gpioport)
{
	// Export the pin to the GPIO directory
	FILE *fp = fopen("/sys/class/gpio/export","w");
	fprintf(fp,"%d",gpioport);
	fclose(fp);

	// Set the pin as an output
	char filename[256];
	sprintf(filename,"/sys/class/gpio/gpio%d/direction",gpioport);
	fp = fopen(filename,"w");
	if(!fp)
	{
		panic("Could not open gpio file");
	}
	fprintf(fp,"out");
	fclose(fp);

	// Open the value file and return a pointer to it.
	sprintf(filename,"/sys/class/gpio/gpio%d/value",gpioport);
	fp = fopen(filename,"w");
	if(!fp)
	{
		panic("Could not open gpio file");
	}
	return fp;
}

void setiopin(FILE *fp, int val)
{
	fprintf(fp,"%d\n",val);
	fflush(fp);
}

void end_gpio(int gpioport, FILE* fp)
{
	fclose(fp);
	fp = fopen("/sys/class/gpio/unexport","w");
	fprintf(fp,"%d",gpioport);
	fclose(fp);
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

void dumptimestamps(int unused)
{
	FILE *fp = fopen("dumpfile.txt","w");
	int i;
	for(i=1; i < MAX_LOGENTRIES; i++)
	{
		if((t[i].tv_sec > 0) && (t[i-1].tv_sec > 0))
		{
			if(t[i].tv_sec==t[i-1].tv_sec)
			{
				fprintf(fp,"%09d\n", (int) (t[i].tv_nsec-t[i-1].tv_nsec));
			}
		}
	}
	fclose(fp);
	end_gpio(PIN_VALUE, pin0);
	exit(0);
}