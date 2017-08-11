#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int a;
	a = system("./teste_retorno");
	// Eh possivel que system() retorne o valor de saida
	// de ./teste_retorno multiplicado por 256. Confira
	// o resultado na sua distribuicao.
	printf("O dobro do valor inserido eh %d\n", a/256);
	//printf("O dobro do valor inserido eh %d\n", a);
	return 0;
}