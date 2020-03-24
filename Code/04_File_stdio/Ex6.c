#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE * abre_arq(char* arquivo, char *modo);

int main()
{
	FILE *fp;
	char string[100];
	fp = abre_arq("arquivo.txt", "w");
	do
	{
		printf("\nDigite uma nova string."
			" Para terminar, digite <enter>: ");
		gets(string);
		fputs(string, fp);
		putc('\n', fp);
	} while(strlen(string) > 0);
	fclose(fp);
}

FILE * abre_arq(char* arquivo, char *modo)
{
	FILE *p = fopen(arquivo, modo);
	if(p==NULL)
	{
		printf("Erro! Impossivel abrir o arquivo!\n");
		exit(-1);
	}
	return p;
}