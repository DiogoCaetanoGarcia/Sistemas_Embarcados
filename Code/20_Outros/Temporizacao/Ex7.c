#include <stdio.h>
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
		if(t[1].tv_nsec>1e9)
		{
			t[1].tv_nsec -= 1e9;
			t[1].tv_sec  += 1;
		}
		clock_nanosleep(CLOCK_MONOTONIC,
			TIMER_ABSTIME, &t[1],  NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &t[1]);
	media = difftime(t[1].tv_sec,
		t[0].tv_sec)*1.0E9;
	media += (float)(t[1].tv_nsec -
			t[0].tv_nsec);
	media /= (float)N;
	printf("Cálculo de tempo usando "
		"clock_gettime():\n");
	printf("N = %d\n", N);
	printf("Media de tempo de clock_nanosleep(%d)\n"
		"   %2.1f us\n",
		DELAY_NS, media/1000.0);
}