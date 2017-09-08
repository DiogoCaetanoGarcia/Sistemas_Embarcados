#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char msgs[500];
	int i;
	int pid[2];
	int fd[2];
	pipe(fd);
	pid[0] = fork();
	if(pid[0] == 0)
	{
		sprintf(msgs, "FILHO1: Quando o vento passa, é a bandeira que se move.");
		write(fd[1], msgs, strlen(msgs)+1);
	}
	else
	{
		pid[1] = fork();
		if(pid[1]==0)
		{
			i = -1;
			do
			{
				i++;
				read(fd[0], msgs+i, 1);
			}while(msgs[i]!='\0');
			printf("%s\n", msgs);
			sprintf(msgs, "FILHO2: Não, é o vento que se move.");
			write(fd[1], msgs, strlen(msgs)+1);
		}
		else
		{
			usleep(50000); // Espera os filhos falarem
			i = -1;
			do
			{
				i++;
				read(fd[0], msgs+i, 1);
			}while(msgs[i]!='\0');
			printf("%s\n", msgs);
			puts("PAI: Os dois se enganam. É a mente dos senhores que se move.");
		}
	}
	

	/*	char buffer_filho[30], msg_filho[30] = "FILHO DIZ: HELLO PIPE";
		printf("Filho vai ler o pipe\n");
		if(read(fd[0], buffer_filho, 30) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Valor lido pelo filho = %s\n", buffer_filho);
		printf("Filho vai escrever no pipe\n");
		if (write(fd[1], msg_filho, sizeof(msg_filho)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Filho terminou de escrever no pipe\n");
	}
	// Codigo do pai
	else
	{
		char buffer_pai[30], msg_pai[30] = "PAI DIZ: HELLO PIPE";
		printf("Pai vai escrever no pipe\n");
		if (write(fd[1], msg_pai, sizeof(msg_pai)) < 0)
			printf("Erro na escrita do pipe\n");
		printf("Pai terminou de escrever no pipe\n");
		printf("Pai vai hibernar por 1 segundo, para dar tempo do filho ler o pipe\n");
		sleep(1);
		printf("Pai vai ler o pipe\n");
		if(read(fd[0], buffer_pai, 30) < 0) 
			printf("Erro na leitura do pipe\n");
		else
			printf("Valor lido pelo pai = %s\n", buffer_pai);
	}*/
	return 0;
}
