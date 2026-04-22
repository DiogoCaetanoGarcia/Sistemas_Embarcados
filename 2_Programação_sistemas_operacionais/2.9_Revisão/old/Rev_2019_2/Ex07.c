#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int fim_espera=0;

void tratamento_SIGUSR1()
{
	fim_espera=1;
}

int main(void)
{
	char frase_in[100], frase_out[100];
	pid_t pid_filho;
	int fd[2];	// Descritores do pipe
	pipe(fd); // Cria o pipe
	signal(SIGUSR1, tratamento_SIGUSR1);
	pid_filho = fork();
	if(pid_filho==0)
	{
		strcpy(frase_out, "Pai, qual é a verdadeira essência da sabedoria?");
		write(fd[1], frase_out, 100);
		fim_espera=0;
		while(fim_espera==0);
		read(fd[0], frase_in, 100);
		printf("PAI: %s\n", frase_in);
		strcpy(frase_out, "Mas até uma criança de três anos sabe disso!");
		write(fd[1], frase_out, 100);
		kill(getppid(),SIGUSR1);
		fim_espera=0;
		while(fim_espera==0);
		read(fd[0], frase_in, 100);
		printf("PAI: %s\n", frase_in);
		kill(getppid(),SIGUSR1);
	}
	else
	{
		read(fd[0], frase_in, 100);
		printf("FILHO: %s\n", frase_in);
		strcpy(frase_out, "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");
		write(fd[1], frase_out, 100);
		kill(pid_filho,SIGUSR1);
		fim_espera=0;
		while(fim_espera==0);
		read(fd[0], frase_in, 100);
		printf("FILHO: %s\n", frase_in);
		strcpy(frase_out, "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
		write(fd[1], frase_out, 100);
		kill(pid_filho,SIGUSR1);
		fim_espera=0;
		while(fim_espera==0);
	}
	return 0;
}