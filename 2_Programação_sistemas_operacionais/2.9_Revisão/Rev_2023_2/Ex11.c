#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Código com um pipe
int main(void)
{
	char str_in[100], str_out[100];
	pid_t pid_filho;
	int fd[2];

	pipe(fd);
	pid_filho = fork();
	if(pid_filho==0)
	{
		strcpy(str_out, "Pai, qual é a verdadeira essência da sabedoria?");
		write(fd[1], str_out, 100);
		sleep(1);
		read(fd[0], str_in, 100);
		printf("PAI: %s\n", str_in);
		strcpy(str_out, "Mas até uma criança de três anos sabe disso!");
		write(fd[1], str_out, 100);
		sleep(1);
		read(fd[0], str_in, 100);
		printf("PAI: %s\n", str_in);
	}
	else
	{
		read(fd[0], str_in, 100);
		printf("FILHO: %s\n", str_in);
		strcpy(str_out, "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");
		write(fd[1], str_out, 100);
		sleep(1);
		read(fd[0], str_in, 100);
		printf("FILHO: %s\n", str_in);
		strcpy(str_out, "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
		write(fd[1], str_out, 100);
		sleep(1);
	}
	return 0;
}


// Código com dois pipes
/*
int main(void)
{
	int pipe_pf[2], pipe_fp[2];
	pipe(pipe_pf);
	pipe(pipe_fp);
	pid_filho = fork();
	if(pid_filho==0)
	{
		strcpy(str_out, "Pai, qual é a verdadeira essência da sabedoria?");
		write(pipe_fp[1], str_out, 100);
		read(pipe_pf[0], str_in, 100);
		printf("PAI: %s\n", str_in);
		strcpy(str_out, "Mas até uma criança de três anos sabe disso!");
		write(pipe_fp[1], str_out, 100);
		read(pipe_pf[0], str_in, 100);
		printf("PAI: %s\n", str_in);
	}
	else
	{
		read(pipe_fp[0], str_in, 100);
		printf("FILHO: %s\n", str_in);
		strcpy(str_out, "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");
		write(pipe_pf[1], str_out, 100);
		read(pipe_fp[0], str_in, 100);
		printf("FILHO: %s\n", str_in);
		strcpy(str_out, "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
		write(pipe_pf[1], str_out, 100);
		wait(NULL);
	}
	return 0;
}*/

/*
// Código com sinais e um pipe

#include <signal.h>

void f_dummy()
{
}

int main(void)
{
	char str_in[100], str_out[100];
	pid_t pid_filho;
	int fd[2];

	signal(SIGUSR1, f_dummy);
	pipe(fd);
	pid_filho = fork();
	if(pid_filho==0)
	{
		strcpy(str_out, "Pai, qual é a verdadeira essência da sabedoria?");
		write(fd[1], str_out, 100);
		pause();
		read(fd[0], str_in, 100);
		printf("PAI: %s\n", str_in);
		strcpy(str_out, "Mas até uma criança de três anos sabe disso!");
		write(fd[1], str_out, 100);
		kill(getppid(), SIGUSR1);
		pause();
		read(fd[0], str_in, 100);
		printf("PAI: %s\n", str_in);
	}
	else
	{
		read(fd[0], str_in, 100);
		printf("FILHO: %s\n", str_in);
		strcpy(str_out, "Não façais nada violento, praticai somente aquilo que é justo e equilibrado.");
		write(fd[1], str_out, 100);
		kill(pid_filho, SIGUSR1);
		pause();
		read(fd[0], str_in, 100);
		printf("FILHO: %s\n", str_in);
		strcpy(str_out, "Sim, mas é uma coisa difícil de ser praticada até mesmo por um velho como eu...");
		write(fd[1], str_out, 100);
		kill(pid_filho, SIGUSR1);
		wait(NULL);
	}
	return 0;
}*/