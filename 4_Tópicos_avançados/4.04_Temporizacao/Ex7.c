#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 150
#define DELAY_NS 10000000
int main(void)
{
	unsigned int i;
	struct timespec t[2];
	double media;

	clock_gettime(CLOCK_MONOTONIC, &t[0]);
	t[1].tv_sec = t[0].tv_sec;
	t[1].tv_nsec = t[0].tv_nsec;
	for(i=1; i<=N; i++)
	{
		t[1].tv_nsec += DELAY_NS;
		while(t[1].tv_nsec>1000000000L)
		{
			t[1].tv_nsec -= 1000000000L;
			t[1].tv_sec++;
		}
		clock_nanosleep(CLOCK_MONOTONIC,
			TIMER_ABSTIME, &t[1],  NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &t[1]);
	media = ((float)difftime(t[1].tv_sec,
		t[0].tv_sec))*1.0E9;
	media += (float)(t[1].tv_nsec -
			t[0].tv_nsec);
	media /= (float)N;
	printf("Media de tempo de clock_nanosleep(%d)\n"
		"   N =  %d, %2.1f us\n",
		DELAY_NS, N, media/1000.0);
}
