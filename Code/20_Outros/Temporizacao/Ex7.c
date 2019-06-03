#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define N 150
#define DELAY_NS 10000000 
int main(void)
{
	unsigned int i;
	struct timespec t[2];
	double dummy_calc, media;
	long diff_ts;

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
	printf("clock_gettime(CLOCK_MONOTONIC)\n");
	printf("   retorna o tempo do clock\n");
	printf("   'monotônico' - isto é, não\n");
	printf("   afetado por descontinuidades\n");
	printf("   no tempo do sistema (p.ex.,\n");
	printf("   se o administrador mudar o\n");
	printf("   relógio do sistema.\n");
}

// void sleep_nsec(struct timespec ts, int delay_sec, int delay_nsec)
// {		
// 	ts.tv_nsec += delay_nsec;
// 	ts.tv_sec  += delay_sec;
// 	clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts,  NULL);
// }

// int main(void)
// {
// 	unsigned int i;
// 	struct timespec t1, t2;
// 	double dummy_calc;
// 	long diff_ts;
// 	clock_gettime(CLOCK_MONOTONIC, &t1);
// 	sleep_nsec(t1, 1, 0);
// 	clock_gettime(CLOCK_MONOTONIC, &t2);
// 	diff_ts = t2.tv_nsec - t1.tv_nsec;
// 	dummy_calc = difftime(t2.tv_sec, t1.tv_sec);
// 	if(dummy_calc>0.0)
// 			diff_ts += 1E9L;
// 	printf("Atraso de sleep_nsec(1s, 0ns): %f s\n",
// 		((float)diff_ts)/1.0E9);
// }