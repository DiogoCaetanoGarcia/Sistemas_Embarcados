#include <stdio.h>

// Para a função exit()
#include <stdlib.h>

int main(int argc, const char * argv[])
{
	FILE *fp;
	fp = fopen("exemplo.bin","wb");
	if (!fp)
	{
		printf("Erro na abertura do arquivo.");
		printf(" Fim de programa.");
		exit(1);
	}
	fclose(fp);
	return 0;
}