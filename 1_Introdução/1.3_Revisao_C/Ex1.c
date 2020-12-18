#include <stdio.h>

int main(void)
{
	//SOE(1) Declaração de um vetor de 5 posições
	char v[] = {5,4,3,2,1};
	//SOE(1) Declaração de um vetor de 6 posições (incluindo \0)
	char palavra2[] = "Texto";
	//SOE(1) Declaração de um vetor de 5 posições
	char palavra1[5] = {'t', 'E', 'X', 'T', 'O'};
	//SOE(4) Interpretação de valores do vetor como inteiros
	printf("%d %d %d %d %d %d\n",
		palavra2[0], palavra2[1],
		palavra2[2], palavra2[3],
		palavra2[4], palavra2[5]);
	//SOE(4) Interpretação de valores do vetor como caracteres
	printf("%c %c %c %c %c %c\n",
		palavra2[0], palavra2[1],
		palavra2[2], palavra2[3],
		palavra2[4], palavra2[5]);
	//SOE(1) Interpretação de valores do vetor como uma string
	printf("%s\n", palavra2);
	//SOE(1) Interpretação de valores do vetor como uma string, sendo que não a terminamos com um \0
	printf("%s\n", palavra1);
	return 0;
}
