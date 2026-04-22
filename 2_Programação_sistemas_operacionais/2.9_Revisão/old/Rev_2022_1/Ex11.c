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
}