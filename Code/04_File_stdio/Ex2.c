#include <stdio.h>
#include <stdlib.h>

void erro_fopen(FILE *fp)
{
	if (fp==NULL)
	{
		printf("Erro na abertura do arquivo.\n");
		printf(" Fim de programa.\n");
		exit(1);
	}
}

int main(int argc, const char * argv[])
{
	FILE *fp;
	fp = fopen("exemplo.bin","wb");
	erro_fopen(fp);
	printf("Arquivo aberto com sucesso.\n");
	fclose(fp);
	return 0;
}