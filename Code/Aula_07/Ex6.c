#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void tratamento_SIGUSR1()
{
	printf("Processo %d recebeu sinal SIGUSR1... ele vai parar agora.\n", getpid());
	exit(1);
}

int main()
{
	int pid_filho;
	signal(SIGUSR1, tratamento_SIGUSR1);
	printf("Processo pai   [%d] vai criar o filho e dormir por 1 segundo.\n", getpid());
	if((pid_filho=fork())==0) 
	{
		printf("Processo filho [%d] vai entrar num loop infinito.\n", getpid());
		while(1);
	}
	else
	{
		sleep(1);
		printf("Processo %d vai enviar o sinal SIGUSR1 para o processo %d\n", getpid(), pid_filho);
		kill(pid_filho,SIGUSR1);
		printf("Processo %d vai dormir por 1 segundo.\n", getpid());
		sleep(1);
	}
	printf("Processo %d encerrando.\n", getpid());
	exit(0); 
}