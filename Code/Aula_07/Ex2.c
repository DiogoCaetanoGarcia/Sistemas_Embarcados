#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int pid;	// PID do processo filho
	int fd[2];	// Descritores do pipe
	char mensagem[30] = "HELLO PIPE";
	// Cria o pipe
	pipe(fd);
	// Cria o processo
	pid = fork();
	// Codigo do pai
	if(pid != 0)
	{
		printf("Pai vai ler o pipe\n");
		if(read(fd[0], mensagem, 30) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Pai leu: %s\n", mensagem);
	}
	// Codigo do filho
	else
	{
		printf("Filho vai escrever no pipe\n");
		if (write(fd[1], mensagem, sizeof(mensagem)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Filho terminou de escrever no pipe\n");
	}
	return 0;
}
