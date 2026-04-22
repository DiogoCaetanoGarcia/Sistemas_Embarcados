#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char nome[1000];
	char nome_arq[1004];
	FILE* fp;
	int idade;

	printf("Digite o seu nome: ");
	scanf("%s", nome);
	sprintf(nome_arq, "%s.txt", nome);
	// strcpy(nome_arq, nome);
	// strcat(nome_arq, ".txt");
	fp = fopen(nome_arq, "w");
	fprintf(fp, "Nome: %s\n", nome);
	printf("Digite a sua idade: ");
	scanf("%d", &idade);
	fprintf(fp, "Idade: %d\n", idade);
	fclose(fp);
	return 0;
}
