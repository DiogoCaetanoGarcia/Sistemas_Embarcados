#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *arq, *chave = argv[1];
	int tamanho_arq, i_arq, i_chave, cont;
	FILE* fp;
	fp = fopen(argv[2], "r");
	fseek(fp, 0, SEEK_END);
	tamanho_arq = ftell(fp);
	arq = (char*)malloc(tamanho_arq);
	rewind(fp); //fseek(fp, 0, SEEK_SET);
	fread(arq, sizeof(char), tamanho_arq, fp);
	fclose(fp);
	for(cont=i_chave=i_arq=0; i_arq<tamanho_arq; i_arq++)
	{
		if(arq[i_arq]==chave[i_chave])
		{
			i_chave++;
			if(chave[i_chave]=='\0')
			{
				cont++;
				i_chave=0;
			}
		}
		else
		{
			i_chave=0;
		}
	}
	printf("'%s' ocorre %d vezes no arquivo '%s'.\n",
		chave, cont, argv[2]);
	free(arq);
	return 0;
}