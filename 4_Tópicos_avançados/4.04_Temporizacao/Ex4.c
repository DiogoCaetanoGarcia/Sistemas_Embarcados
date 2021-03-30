#include <stdio.h>
#include <time.h>

#define N 150000000
int main(void)
{
	unsigned int i;
	clock_t CPU_time_1, CPU_time_2;
	// Quantidade de ciclos de
	// clock desde o começo
	// da execução do processo
	CPU_time_1 = clock();
	for(i = 0; i < N; i++);
	// Quantidade de ciclos de
	// clock desde o começo
	// da execução do processo
	CPU_time_2 = clock();
	puts("Análise por ciclos de clock");
	printf("- Ciclos de clock "
		"antes do laço for: %ld\n",
		CPU_time_1);
	printf("- Ciclos de clock "
		"depois  do laço for: %ld\n",
		CPU_time_2);
	printf("- Diferença: %ld ciclos\n",
		CPU_time_2-CPU_time_1);
	puts("Análise por tempo");
	printf("- CLOCKS_PER_SEC = %10.1f\n",
		(float)CLOCKS_PER_SEC);
	printf("- Tempo antes "
		"do laço for: %4.1f ms\n", 
		((float)CPU_time_1)/
		CLOCKS_PER_SEC*1000.0);
	printf("- Tempo depois "
		"do laço for: %4.1f ms\n", 
		((float)CPU_time_2)/
		CLOCKS_PER_SEC*1000.0);
	printf("- Diferença: %4.1f ms\n",
		((float)(CPU_time_2-CPU_time_1))/CLOCKS_PER_SEC*1000.0);
}