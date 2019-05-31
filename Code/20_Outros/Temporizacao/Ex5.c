#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	unsigned int i;
	clock_t CPU_time_1, CPU_time_2;
	CPU_time_1 = clock();
	usleep(1E6);
	CPU_time_2 = clock();
	printf("Atraso de usleep(1E6): %f s\n\n",
		((float)(CPU_time_2-CPU_time_1))/CLOCKS_PER_SEC);
	printf("clock() retorna a quantidade\n");
	printf("   de ciclos de clock consumidos\n");
	printf("   PELO PROCESSO ATUAL.\n");
}