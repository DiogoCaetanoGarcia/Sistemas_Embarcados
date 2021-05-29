#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define N 150
#define DELAY_US 10000 
int main(void)
{
	unsigned int i;
	struct timespec t[2];
	double media;

	clock_gettime(CLOCK_MONOTONIC, &t[0]);
	for(i=1; i<=N; i++)
		usleep(DELAY_US);
	clock_gettime(CLOCK_MONOTONIC, &t[1]);
	media = difftime(t[1].tv_sec,
		t[0].tv_sec)*1.0E9;
	media += (float)(t[1].tv_nsec -
			t[0].tv_nsec);
	media /= (float)N;
	printf("Media de tempo de usleep(%d)\n"
		"   N =  %d, %2.1f us\n",
		DELAY_US, N, media/1000.0);
}