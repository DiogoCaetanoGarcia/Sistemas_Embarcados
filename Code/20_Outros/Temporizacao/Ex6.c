#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	unsigned int i;
	struct timespec t1, t2;
	double dummy_calc;
	long diff_ts;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	usleep(1E6);
	clock_gettime(CLOCK_MONOTONIC, &t2);
	diff_ts = t2.tv_nsec - t1.tv_nsec;
	dummy_calc = difftime(t2.tv_sec, t1.tv_sec);
	if(dummy_calc>0.0)
			diff_ts += 1000*1000*1000;
	printf("Atraso de usleep(1E6): %f s\n\n",
		((float)diff_ts)/1.0E9);
	printf("clock_gettime(CLOCK_MONOTONIC)\n");
	printf("   retorna o tempo do clock\n");
	printf("   'monotônico' - isto é, não\n");
	printf("   afetado por descontinuidades\n");
	printf("   no tempo do sistema (p.ex.,\n");
	printf("   se o administrador mudar o\n");
	printf("   relógio do sistema.\n");

}