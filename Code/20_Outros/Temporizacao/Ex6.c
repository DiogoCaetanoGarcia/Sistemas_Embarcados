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
	printf("Cálculo de tempo usando "
		"clock_gettime():\n");
	printf("N = %d\n", N);
	printf("Media de tempo de usleep(%d)\n"
		"   %2.1f us\n",
		DELAY_US, media/1000.0);
	printf("clock_gettime(CLOCK_MONOTONIC)\n");
	printf("   retorna o tempo do clock\n");
	printf("   'monotônico' - isto é, não\n");
	printf("   afetado por descontinuidades\n");
	printf("   no tempo do sistema (p.ex.,\n");
	printf("   se o administrador mudar o\n");
	printf("   relógio do sistema.\n");
}