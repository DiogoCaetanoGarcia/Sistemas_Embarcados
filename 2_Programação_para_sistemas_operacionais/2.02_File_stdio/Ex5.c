#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE * abre_arq(char* arquivo, char *modo);
void le_arq(FILE *p);

int main(int argc, const char * argv[])
{
	FILE *p;
	char str[100], c;
	char frase[120] = "Este e um arquivo chamado: ";
	printf("Entre com um nome para o arquivo:\n");
	gets(str);
	p = abre_arq(str, "w");
	strcat(frase, str);
	fputs(frase, p);
	putc('\n', p);
	fclose(p);
	p = abre_arq(str, "r");
	le_arq(p);
	fclose(p);
	return 0;
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
	char c = getc(p);
	while( c != EOF )
	{
		printf("%c", c);
		c = getc(p);
	}
}