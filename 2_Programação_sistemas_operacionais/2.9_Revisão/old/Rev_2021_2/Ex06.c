#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* le_arquivo(char *nome_arquivo)
{
	FILE *fp;
	int tamanho_arq;
	char *conteudo_arq;

	fp = fopen(nome_arquivo, "r");
	fseek(fp, 0, SEEK_END);
	tamanho_arq = ftell(fp);
	rewind(fp); //fseek(fp, 0, SEEK_SET);
	conteudo_arq = (char*)malloc(tamanho_arq*sizeof(char));
	fread(conteudo_arq, sizeof(char), tamanho_arq, fp);
	fclose(fp);
	return conteudo_arq;
}

int conta_palavra(char* conteudo, char* palavra_chave)
{
	int contagem = 0;
	char *conteudo_encontrado;
	conteudo_encontrado = strstr(conteudo, palavra_chave);
	while(conteudo_encontrado!=NULL)
	{
		contagem++;
		conteudo_encontrado++;
		conteudo_encontrado = strstr(conteudo_encontrado, palavra_chave);
	}
	return contagem;
}

int main(int argc, char *argv[])
{
	char *cnt_arq;
	int cnt;
	cnt_arq = le_arquivo(argv[2]);
	cnt = conta_palavra(cnt_arq, argv[1]);
	if(cnt==1)
		printf("'%s' ocorre 1 vez no arquivo '%s'.\n",
			argv[1], argv[2]);
	else
		printf("'%s' ocorre %d vezes no arquivo '%s'.\n",
			argv[1], cnt, argv[2]);
	free(cnt_arq);
	return 0;
}
