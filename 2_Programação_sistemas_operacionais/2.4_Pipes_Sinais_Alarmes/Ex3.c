#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int pid;
	int fd[2];
	pipe(fd);
	pid = fork();
	if(pid == 0) // Codigo do filho
	{
		char buffer_filho[30], msg_filho[30] = "FILHO DIZ: HELLO PIPE";
		printf("Filho vai ler o pipe\n");
		if(read(fd[0], buffer_filho, 30) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Valor lido pelo filho = %s\n", buffer_filho);
		printf("Filho vai escrever no pipe\n");
		if (write(fd[1], msg_filho, 30) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Filho terminou de escrever no pipe\n");
	}
	else // Codigo do pai
	{
		char buffer_pai[30], msg_pai[30] = "PAI DIZ: HELLO PIPE";
		printf("Pai vai escrever no pipe\n");
		if (write(fd[1], msg_pai, 30) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Pai terminou de escrever no pipe\n");
		printf("Pai vai hibernar por 1 segundo, para dar tempo do filho ler o pipe\n");
		sleep(1);
		printf("Pai vai ler o pipe\n");
		if(read(fd[0], buffer_pai, 30) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Valor lido pelo pai = %s\n", buffer_pai);
	}
	return 0;
}
