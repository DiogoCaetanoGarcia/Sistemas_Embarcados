#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	char frase_in[100], frase_out[100];
	pid_t pid_filhos[2];
	int fd_s1_to_s2[2], fd_s2_to_f[2], fd_f_to_s1[2];
	pipe(fd_s1_to_s2);
	pipe(fd_s2_to_f);
	pipe(fd_f_to_s1);
	pid_filhos[0] = fork();
	if(pid_filhos[0]==0)
	{
		strcpy(frase_out, "Quando o vento passa, é a bandeira que se move.");
		write(fd_s1_to_s2[1], frase_out, 100);
		read(fd_f_to_s1[0], frase_in, 100);
		printf("PAI:    %s\n", frase_in);
	}
	else
	{
		pid_filhos[1] = fork();
		if(pid_filhos[1]==0)
		{
			read(fd_s1_to_s2[0], frase_in, 100);
			printf("FILHO1: %s\n", frase_in);
			strcpy(frase_out, "Não, é o vento que se move.");
			write(fd_s2_to_f[1], frase_out, 100);
		}
		else
		{
			read(fd_s2_to_f[0], frase_in, 100);
			printf("FILHO2: %s\n", frase_in);
			strcpy(frase_out, "Os dois se enganam. É a mente dos senhores que se move.");
			write(fd_f_to_s1[1], frase_out, 100);
			wait(NULL);
		}
	}
	return 0;
}