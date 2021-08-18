#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		printf("Indique o nome do arquivo e a palavra a procurar.\n");
		return -1;
	}
	char *texto;
	int contagem, i;
	char *l;
	FILE *fp = fopen(argv[2], "r");
	// Calculando tamanho do arquivo
	int tamanho = 0;
	char c = getc(fp);
	while( c != EOF )
	{
		tamanho++;
		c = getc(fp);
	}
	// Alocando memória e lendo o arquivo
	texto = (char*) malloc(tamanho*sizeof(char));
	rewind(fp);
	fread(texto, sizeof(char), tamanho, fp);
	fclose(fp);
	// Procura string várias vezes usando strstr()
	l = strstr(texto, argv[1]);
	while(l!=NULL)
	{
		contagem++;
		l += strlen(argv[1]);
		l = strstr(l, argv[1]);
	}
	// Imprime resultado
	if(contagem==1)
		printf("'%s' ocorre 1 vez no arquivo '%s'.\n",
			argv[1], argv[2]);
	else
		printf("'%s' ocorre %d vezes no arquivo '%s'.\n",
			argv[1], contagem, argv[2]);
	free(texto);
	return 0;
}