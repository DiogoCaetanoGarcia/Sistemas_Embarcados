#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int a;
	a = system("./teste_retorno.out");
	printf("Valor de retorno: %d\n", a);
	printf("Dobro do valor inserido = %d\n", a/256);
	return 0;
}