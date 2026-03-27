#include "file_stdio.h"

void erro_fopen(FILE *fp)
{
	if (fp==NULL)
	{
		printf("Erro na abertura do arquivo.\n");
		printf(" Fim de programa.\n");
		exit(1);
	}
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

void le_arq(FILE *p)
{
	int c = getc(p);
	while( c != EOF )
	{
		printf("%c", c);
		c = getc(p);
	}
}
