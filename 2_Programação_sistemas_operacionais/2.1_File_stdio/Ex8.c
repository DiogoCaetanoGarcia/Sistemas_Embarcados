#include <stdio.h>
#include <stdlib.h>
#include "file_stdio.h"

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
