#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	FILE* fp;
	char nome_arq[304];
	if(argc<3)
	{
		printf("Indique o nome e a idade nos argumentos de entrada!\n");
		return -1;
	}
	strcpy(nome_arq, argv[1]);
	strcat(nome_arq, ".txt");
	fp = fopen(nome_arq, "w");
	fprintf(fp, "Nome: %s\nIdade: %s anos\n",
		argv[1], argv[2]);
	fclose(fp);
	return 0;
}
