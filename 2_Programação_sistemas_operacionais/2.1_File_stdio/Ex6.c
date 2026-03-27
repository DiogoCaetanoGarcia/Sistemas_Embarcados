#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_stdio.h"

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
