#include <stdio.h>

int main(void)
{
	//SOE(1) Declaração de um vetor de 3 posições
	char v[] = {5,4,3};
	char *p;
	//SOE(1) Antes,  v = [5 4 3]
	printf("Antes,  v = [%d %d %d]\n", v[0], v[1], v[2]);
	//SOE(1) Considerando que o vetor começa no endereço 1000, p = 1000
	p = &v[0];
	//SOE(1) Vá ao endereço guardado em 'p', e guarde o valor '10'
	*p = 10;
	//SOE(1) Vá um endereço à frente do endereço guardado em 'p', e guarde o valor '20'
	*(p+1) = 20;
	//SOE(1) Considerando que o vetor começa no endereço 1000, p = 1000+2*4 = 1008
	p = &v[2];
	//SOE(1) Vá ao endereço guardado em 'p', e guarde o valor '30' 
	*p = 30;
	//SOE(1) Depois, v = [10 20 30]
	printf("Depois, v = [%d %d %d]\n", v[0], v[1], v[2]);
	return 0;
}
