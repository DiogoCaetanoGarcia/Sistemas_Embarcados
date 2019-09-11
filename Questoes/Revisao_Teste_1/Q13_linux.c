#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
	FILE* fp;
	char nome_arq[100];

	if(argc<3)
	{
		puts("Quantidade insuficiente de argumentos!");
		return -1;
	}
	
	sprintf(nome_arq, "%s.txt", argv[1]);
	fp = fopen(nome_arq, "w");
	if(fp==NULL)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(-1);
	}
	sprintf(nome_arq, "Nome: %s\nIdade: %s\n",
		argv[1], argv[2]);
	fwrite(nome_arq, strlen(nome_arq), sizeof(char), fp);
	fclose(fp);
	return 0;
}
