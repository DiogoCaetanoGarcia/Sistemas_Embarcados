#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int a;
	printf("****************************\n");
	printf("* Chamada system(\"ls -l\"); *\n");
	printf("****************************\n");
	printf("\n");
	a = system("ls -l");
	printf("\n");
	printf("*******************************\n");
	printf("* system() retornou o valor %d *\n", a);
	printf("*******************************\n");
	printf("\n");
	printf("**********************************************************\n");
	printf("* Chamada system(\"ls -l arquivo_inexistente.txt\");       *\n");
	printf("*    (para ler informacoes de um arquivo que não existe) *\n");
	printf("**********************************************************\n");
	printf("\n");
	a = system("ls -l arquivo_inexistente.txt");
	printf("\n");
	printf("*********************************\n");
	printf("* system() retornou o valor %d *\n", a);
	printf("*********************************\n");
	printf("\n");
	printf("*******************************************************\n");
	printf("* Chamada system(\"abcdefghijklmnopqrstuvwxyz\");       *\n");
	printf("*    (para tentar executar um comando que não existe) *\n");
	printf("*******************************************************\n");
	printf("\n");
	a = system("abcdefghijklmnopqrstuvwxyz");
	printf("\n");
	printf("***********************************\n");
	printf("* system() retornou o valor %d *\n", a);
	printf("***********************************\n");
	return 0;
}