// Código com um pipe
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

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
