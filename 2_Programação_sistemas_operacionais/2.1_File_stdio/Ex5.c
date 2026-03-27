#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_stdio.h"

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
