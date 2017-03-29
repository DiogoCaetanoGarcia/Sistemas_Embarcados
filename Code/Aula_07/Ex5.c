#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void funcao_sigsegv()
{
	printf("Recebi segment fault. Vou morrer!!!\n");   
	exit(1);
}

int main()
{
	char *p;
	signal(SIGSEGV, funcao_sigsegv);
	printf("Vou forcar um segment fault.\n");
	printf("%s", *p);
}