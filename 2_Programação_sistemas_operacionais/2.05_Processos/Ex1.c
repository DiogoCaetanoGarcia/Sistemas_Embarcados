#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("Programas em execução:\n");
	system("ps");
	printf ("Identificador do processo (PID) é: %d\n",
		getpid( ));
	printf ("Identificador do processo-pai (PPID): %d\n",
		getppid( ));
	return 0;
}