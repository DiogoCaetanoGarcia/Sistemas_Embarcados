#include <stdio.h>
#include <stdlib.h>

// LEIA-ME!!!! IMPORTANTE!!!!!
// Compile este programa com o nome
//
//    teste_retorno
//
// Este programa retorna o dobro do valor inserido.
// Execute o proximo exemplo para ver o resultado.

int main(int argc, const char *argv[])
{
	int a;
	printf("Insira um valor inteiro: ");
	scanf("%d", &a);
	return 2*a;
}