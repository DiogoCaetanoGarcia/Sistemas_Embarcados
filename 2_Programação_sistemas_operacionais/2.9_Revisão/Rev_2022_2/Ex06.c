#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc<3)
	{
		printf("Indique a palavra-chave e o nome do arquivo nos argumentos de entrada!\n");
		return -1;
	}
	char *conteudo, *palavra;
	int tam, contagem = 0, i1, i2;
	FILE* fp = fopen(argv[2], "r");
	fseek(fp, 0, SEEK_END);
	tam = ftell(fp);
	rewind(fp);
	conteudo = (char*) malloc(tam);
	fread(conteudo, sizeof(char), tam, fp);
	fclose(fp);
	palavra = argv[1];
	for(i1=0, i2=0; i1<tam; i1++)
	{
		if(conteudo[i1]==palavra[i2])
		{
			i2++;
			if(palavra[i2]=='\0')
			{
				contagem++;
				i2=0;
			}
		}
		else
			i2=0;
	}
	printf("'%s' ocorre %d vezes no arquivo '%s'.\n",
		palavra, contagem, argv[2]);
	free(conteudo);
	return 0;
}