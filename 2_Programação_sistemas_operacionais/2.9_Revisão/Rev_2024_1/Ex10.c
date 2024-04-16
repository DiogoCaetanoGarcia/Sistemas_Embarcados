#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	pid_t pid_pai = getpid(), pid_filho;
	char *lista_de_argumentos[] = {NULL, NULL};
	int i;

	for(i=1; i<argc; i++)
	{
		if(getpid() == pid_pai)
		{
			pid_filho = fork();
			if(pid_filho==0)
			{
				lista_de_argumentos[0] = argv[i];
				execvp(lista_de_argumentos[0], lista_de_argumentos);
				printf("Comando '%s' deu erro!\n", argv[i]);
			}
			else
			{
				wait(NULL);
			}
		}
	}
	printf("Processo %d terminando!\n", getpid());
	return 0;
}