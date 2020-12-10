#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define N 10000
#define FAT 20

unsigned long long int fatorial(unsigned int n)
{
	if(n<2)
		return 1;
	else return n*fatorial(n-1);
}

int main(void)
{
	unsigned long long int f;
	unsigned int i;
	struct timespec t[2];
	double media;

	clock_gettime(CLOCK_MONOTONIC, &t[0]);
	for(i=1; i<=N; i++)
		f = fatorial(FAT);
	clock_gettime(CLOCK_MONOTONIC, &t[1]);
	media = difftime(t[1].tv_sec,
		t[0].tv_sec)*1.0E9;
	media += (float)(t[1].tv_nsec -
			t[0].tv_nsec);
	media /= (float)N;
	printf("Media de tempo de "
		"fatorial(%d) = %lld\n"
		"   %2.1f ns\n",
		FAT, f, media);
}