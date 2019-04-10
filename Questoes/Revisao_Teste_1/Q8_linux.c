#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define N 100

int main()
{
	int pid;
	int fd[2];
	pipe(fd);
	pid = fork();
	// Codigo do filho
	if(pid == 0)
	{
		char buffer_filho[N], msg_filho[N];
		sprintf(msg_filho, "Pai, qual é a verdadeira essência da sabedoria?");
		write(fd[1], msg_filho, N);
		sleep(1);
		read(fd[0], buffer_filho, N);
		printf("PAI: %s\n", buffer_filho);
		sprintf(msg_filho, "Mas até uma criança de três anos sabe disso!");
		write(fd[1], msg_filho, N);
		sleep(1);
		read(fd[0], buffer_filho, N);
		printf("PAI: %s\n", buffer_filho);
	}
	// Codigo do pai
	else
	{
		char buffer_pai[N], msg_pai[N];
		read(fd[0], buffer_pai, N);
		printf("FILHO: %s\n", buffer_pai);
		sprintf(msg_pai, "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");
		write(fd[1], msg_pai, N);
		sleep(1);
		read(fd[0], buffer_pai, N);
		printf("FILHO: %s\n", buffer_pai);
		sprintf(msg_pai, "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
		write(fd[1], msg_pai, N);
		wait(NULL);
	}
	return 0;
}
