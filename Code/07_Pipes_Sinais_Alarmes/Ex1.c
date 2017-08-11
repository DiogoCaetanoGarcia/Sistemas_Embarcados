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
	// Codigo do filho
	if(pid == 0)
	{
		printf("Filho vai ler o pipe\n");
		if(read(fd[0], mensagem, 30) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Filho leu: %s\n", mensagem);
	}
	// Codigo do pai
	else
	{
		printf("Pai vai escrever no pipe\n");
		if (write(fd[1], mensagem, sizeof(mensagem)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Pai terminou de escrever no pipe\n");
	}
	return 0;
}
