#include <stdio.h>
#include <time.h>

#define N 150000000
int main(void)
{
	unsigned int i;
	time_t time_1, time_2;
	// Hora atual do sistema
	time_1 = time(NULL);
	for(i = 0; i < N; i++);
	// Hora atual do sistema
	// após o laço 'for'
	time_2 = time(NULL);
	printf("Tempo de execução do laço 'for': %4.1f s\n",
		difftime(time_2, time_1));
}