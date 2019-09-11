#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
	int fp;
	char nome_arq[100];

	if(argc<3)
	{
		puts("Quantidade insuficiente de argumentos!");
		return -1;
	}
	
	sprintf(nome_arq, "%s.txt", argv[1]);
	fp = open(nome_arq,
		O_RDWR | O_CREAT, S_IRWXU);
	if(fp==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(-1);
	}
	sprintf(nome_arq, "Nome: %s\nIdade: %s\n",
		argv[1], argv[2]);
	write(fp, nome_arq, strlen(nome_arq));
	close(fp);
	return 0;
}
