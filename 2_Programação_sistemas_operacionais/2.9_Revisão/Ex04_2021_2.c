#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char nome[1000];
	char nome_arquivo[1004];
	int idade;
	FILE *fp;
	printf("Digite o seu nome: ");
	scanf("%s", nome);
	printf("Digite a sua idade: ");
	scanf("%d", &idade);
	strcpy(nome_arquivo, nome);
	strcat(nome_arquivo, ".txt");
	fp = fopen(nome_arquivo, "w");
	fprintf(fp, "Nome: %s\n", nome);
	fprintf(fp, "Idade: %d anos\n", idade);
	fclose(fp);
	return 0;
}
