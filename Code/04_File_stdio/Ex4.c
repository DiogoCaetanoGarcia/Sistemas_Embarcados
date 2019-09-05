#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[])
{
	FILE *fp;
	char c;
	fp = fopen("arquivo.txt","r");
	if(!fp)
	{
		printf( "Erro na abertura do arquivo");
		exit(-1);
	}
	// Enquanto não chegar ao final do arquivo
	for(c = getc(fp); c != EOF; c = getc(fp))
	{
		// Imprime o caracter lido
		printf("%c", c);
	}
	printf("\n");
	fclose(fp);
	return 0;
}