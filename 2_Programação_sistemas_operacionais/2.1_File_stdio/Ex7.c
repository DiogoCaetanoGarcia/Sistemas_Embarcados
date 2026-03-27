#include <stdio.h>
#include <stdlib.h>
#include "file_stdio.h"

int main()
{
	FILE *fp;
	float pi = 3.1415;
	float pilido;

	fp = abre_arq("arquivo.bin", "wb");
	if(fwrite(&pi, sizeof(float), 1, fp) != 1)
		printf("Erro na escrita do arquivo");
	fclose(fp);

	fp = abre_arq("arquivo.bin", "rb");
	if(fread(&pilido, sizeof(float), 1, fp) != 1)
		printf("Erro na leitura do arquivo");
	printf("O valor de PI "
		"(lido do arquivo) eh: %f\n",
		pilido);
	fclose(fp);
	return(0);
}
