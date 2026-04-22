#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int pid_filho;
	int fd[2];
	pipe(fd);
	pid_filho = fork();
	if(pid_filho!=0)
	{
		for(int cnt_enviada = 1; cnt_enviada<=10; cnt_enviada++)
		{
			write(fd[1], &cnt_enviada, sizeof(int));
			sleep(1);
		}
	}
	else
	{
		int cnt_recebida;
		do
		{
			read(fd[0], &cnt_recebida, sizeof(int));
			fprintf(stderr, "%d ", cnt_recebida);
		}
		while(cnt_recebida<10);
		fprintf(stderr, "\n");
	}
	return 0;
}
