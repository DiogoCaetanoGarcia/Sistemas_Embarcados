#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int i, pid_filho;
	char *lista_args[] = {NULL, NULL};
	for(i=1; i<argc; i++)
	{
		pid_filho = fork();
		if(pid_filho==0)
		{
			lista_args[0] = argv[i];
			execvp(lista_args[0], lista_args);
			fprintf(stderr, "Erro em %s\n", argv[i]);
			return -1;
		}
		else
			wait(NULL);
	}
	return 0;
}