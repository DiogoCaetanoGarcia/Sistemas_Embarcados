#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void funcao_para_control_c()
{
	printf("\nQuem mandou voce pressionar CTRL-C?\n");
	printf("Vou ter de fechar o programa!\n");
	exit(1);
}

int main()
{
	signal(SIGINT, funcao_para_control_c);
	printf("Pressione CTRL-C para retirar o programa do loop infinito abaixo.\n");
	while(1);
	return 0;
}
