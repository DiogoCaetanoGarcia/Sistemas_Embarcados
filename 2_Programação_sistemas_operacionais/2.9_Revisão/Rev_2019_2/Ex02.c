#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	FILE* fp;
	char *file_content;
	char *palavra, *arq;
	int N, cont_palavra, i_arq, i_palavra;
	if(argc<3)
	{
		printf("Indique a palavra para buscar e o arquivo aonde buscar!\n");
		return -1;
	}
	fp = fopen(argv[2], "r"); // Abre arquivo
	fseek(fp, 0, SEEK_END); // Pula pro final do arquivo
	N = (int) ftell(fp); // Lê tamanho do arquivo
	fseek(fp, 0, SEEK_SET); // Pula pro começo do arquivo
	file_content = (char *)malloc((N+1)*sizeof(char)); // Aloca memória dinamicamente
	fread(file_content, sizeof(char), N, fp); // Lê todo o arquivo
	file_content[N] = '\0';
	fclose(fp);

	palavra = argv[1];
	arq = file_content;
	cont_palavra = 0;
	// Percorre o conteúdo do arquivo
	for(i_arq = 0; i_arq<N; i_arq++)
	{
		// Compara o conteúdo do arquivo com a palavra
		for(i_palavra=0; (arq[i_arq + i_palavra]!='\0') && (palavra[i_palavra]!='\0'); i_palavra++)
		{
			if(arq[i_arq + i_palavra]!=palavra[i_palavra])
			{
				break;
			}
		}
		if(palavra[i_palavra]=='\0')
		{
			cont_palavra++;
		}
	}
	printf("'%s' ocorre %d vezes no arquivo '%s'\n", palavra, cont_palavra, argv[2]);

	free(file_content);
	return 0;
}