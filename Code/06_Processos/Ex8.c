#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	char * lista_de_argumentos[] = { "ls", NULL};
	pid_t pid_filho = fork();
	if(pid_filho == 0)
	{
		printf("Processo-FILHO: ---\n");
		execvp(lista_de_argumentos[0],
			lista_de_argumentos);
		printf("Processo-FILHO: Mensagem escrita se houver"
			" erro de execucao em execvp()\n");
	}
	else
	{
		printf("Processo-PAI: ---\n");
	}
	return 0;
}