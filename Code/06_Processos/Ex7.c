#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	char * lista_de_argumentos[] = { "abcde", NULL};
	pid_t pid_filho = fork();
	if(pid_filho == 0)
	{
		printf("Processo-FILHO: ---\n");
	}
	else
	{
		printf("Processo-PAI: ---\n");
		execvp(lista_de_argumentos[0],
			lista_de_argumentos);
		printf("Processo-PAI: mensagem escrita se houver"
			" erro de execucao em execvp()\n");
	}
	return 0;
}