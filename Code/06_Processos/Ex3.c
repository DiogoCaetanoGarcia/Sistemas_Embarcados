#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main ()
{
	int a = 1, b = 2, c = 3;
	pid_t child_pid;
	printf("**********************************************************\n");
	printf("* O ID de processo do programa principal eh %d.        *\n", (int) getpid ());
	printf("* Vamos executar um fork() agora.                        *\n");
	printf("* Pense nele como uma 'mitose' de um processo.           *\n");
	printf("* Antes do fork(), os seguintes processos estao rodando. *\n");
	printf("**********************************************************\n");
	printf("\n");
	system("ps");
	printf("\n");
	printf("***********************************************************************\n");
	printf("* Viu como getpid() forneceu corretamente o ID deste processo (%d)? *\n", (int) getpid ());
	printf("***********************************************************************\n");
	printf("\n");

	printf("****************************************************\n");
	printf("* Antes de criar o processo-filho, a=%d, b=%d e c=%d. *\n", a, b, c);
	printf("****************************************************\n");
	printf("\n");
	
	child_pid = fork();
	if (child_pid == 0)
	{
		a=7;
		b=8;
		c=9;
		printf("********************************************************************\n");
		printf("* Este texto foi escrito no terminal pelo processo FILHO (ID=%d) *\n", (int) getpid());
		printf("* Repare que cada processo tem sua versao destas variaveis:        *\n");
		printf("*    a = %d                                                         *\n", a);
		printf("*    b = %d                                                         *\n", b);
		printf("*    c = %d                                                         *\n", c);
		printf("* Cuidado com o acesso compartilhado a arquivos!!!                 *\n");
		printf("********************************************************************\n");
		printf("\n");
	}
	else
	{
		sleep(1);
		printf("******************************************************************\n");
		printf("* Este texto foi escrito no terminal pelo processo PAI (ID=%d) *\n", (int) getpid());
		printf("* Seu filho tem o ID %d.                                       *\n", child_pid);
		printf("* Repare que cada processo tem sua versao destas variaveis:      *\n");
		printf("*    a = %d                                                       *\n", a);
		printf("*    b = %d                                                       *\n", b);
		printf("*    c = %d                                                       *\n", c);
		printf("* Cuidado com o acesso compartilhado a arquivos!!!               *\n");
		printf("******************************************************************\n");
		printf("\n");
	}
	
	return 0;
}