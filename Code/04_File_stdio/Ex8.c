#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fp;
	float pi = 3.1415;
	float pilido;
	if((fp = fopen("arquivo.txt", "w")) == NULL)
	{
		printf("Erro na abertura do arquivo");
		exit(1);
	}
	fprintf(fp, "pi = %f\n", pi);
	fclose(fp);

	if((fp = fopen("arquivo.txt", "rb")) == NULL)
	{
		printf("Erro na abertura do arquivo");
		exit(1);
	}
	fscanf(fp, "pi = %f\n", &pilido);
	printf("\nO valor de PI "
		"(lido do arquivo) eh: %f\n\n",
		pilido);
	fclose(fp);
	return(0);
}