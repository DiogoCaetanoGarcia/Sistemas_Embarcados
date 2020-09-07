#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int pid;	// PID do processo filho
	int fd[2];	// Descritores do pipe
	char mensagem[30];
	pipe(fd); // Cria o pipe
	pid = fork(); // Cria o processo
	if(pid == 0) // Codigo do filho
	{
		printf("Filho vai ler o pipe\n");
		if(read(fd[0], mensagem, 30) < 0)
			printf("Erro na leitura do pipe\n");
		else
			printf("Filho leu: %s\n", mensagem);
	}
	else // Codigo do pai
	{
		strcpy(mensagem, "HELLO PIPE");
		printf("Pai vai escrever no pipe\n");
		if (write(fd[1], mensagem, 30) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Pai terminou de escrever no pipe\n");
	}
	return 0;
}
