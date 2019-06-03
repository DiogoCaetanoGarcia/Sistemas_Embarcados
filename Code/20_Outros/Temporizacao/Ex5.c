#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define N 150
#define DELAY_US 10000 
int main(void)
{
	unsigned int i;
	clock_t CPU_time[2];
	float media;
	CPU_time[0] = clock();
	for(i=1; i<=N; i++)
		usleep(DELAY_US);
	CPU_time[1] = clock();
	media += (float)(CPU_time[1]-CPU_time[0]);
	media /= (float)N;
	media /= (float)CLOCKS_PER_SEC;
	printf("Cálculo de tempo usando clock():\n");
	printf("N = %d\n", N);
	printf("Media de tempo de usleep(%d)\n"
		"   %2.1f us\n",
		DELAY_US, media*1.0e6);
	printf("clock() retorna a quantidade\n");
	printf("   de ciclos de clock consumidos\n");
	printf("   PELO PROCESSO ATUAL.\n");
	printf("A chamada usleep(10000) não é\n");
	printf("   contabilizada.\n");
}