#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[])
{
	FILE *fp;
	char string[100];
	int i;
	fp = fopen("arquivo.txt","w");
	if(!fp)
	{
		printf( "Erro na abertura do arquivo");
		exit(0);
	}
	printf("Entre com a string a"
		" ser gravada no arquivo:");
	gets(string);
	// Grava a string, caractere a caractere
	for(i=0; string[i]; i++)
		putc(string[i], fp);
	putc('\n', fp);
	fclose(fp);
	return 0;
}