#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	int pid_filho;
	char *lista_de_argumentos[] = {NULL, NULL};
	for(i=1; i<argc; i++)
	{
		pid_filho = fork();
		if(pid_filho==0)
		{
			lista_de_argumentos[0] = argv[i];
			execvp(lista_de_argumentos[0],
				lista_de_argumentos);
		}
		else
		{
			wait(NULL);
		}
	}
	return 0;
}
