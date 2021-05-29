#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int a;
	printf("Comando: \"ls\"\n");
	a = system("ls");
	printf("Retorno: %d\n\n", a);
	
	printf("Comando: \"ls 12345.txt\"\n");
	a = system("ls 12345.txt");
	printf("Retorno: %d\n\n", a);

	printf("Comando: \"abcde\"\n");
	a = system("abcde");
	printf("Retorno de system(\"abcde\"): %d\n\n", a);
	return 0;
}