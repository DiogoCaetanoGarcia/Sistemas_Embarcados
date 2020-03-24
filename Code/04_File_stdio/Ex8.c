#include <stdio.h>
#include <stdlib.h>
FILE * abre_arq(char* arquivo, char *modo);

int main()
{
	FILE *fp;
	float pi = 3.1415;
	float pilido;

	fp = abre_arq("arquivo.txt", "w");
	fprintf(fp, "pi = %f\n", pi);
	fclose(fp);
	
	fp = abre_arq("arquivo.txt", "r");
	fscanf(fp, "pi = %f\n", &pilido);
	printf("O valor de PI "
		"(lido do arquivo) eh: %f\n",
		pilido);
	fclose(fp);
	return(0);
}

FILE * abre_arq(char* arquivo, char *modo)
{
	FILE *p = fopen(arquivo, modo);
	if(p==NULL)
	{
		printf("Erro! Impossivel abrir o arquivo!\n");
		exit(-1);
	}
	return p;
}