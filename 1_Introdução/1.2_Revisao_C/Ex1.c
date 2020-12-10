#include <stdio.h>
#define PI 3.14159265358979311599796346854419

int main(void)
{
	// Comentario por linha
	char a = 115, b = 116, c = 117;
	/* Comentario
	por bloco*/
	printf("Olá mundo!\n");
	printf("Mesmo valor, diferentes interpretações:\n");
	printf("\ta = %d ('%c' em ASCII)\n", a, a);
	printf("\tb = %d ('%c' em ASCII)\n", b, b);
	printf("\tc = %d ('%c' em ASCII)\n", c, c);
	float d = 0.1, e = 0.2;
	double f = d+e;
	printf("Cuidado com a representação em ponto flutuante:\n");
	printf("\tAtribuímos 0.1 a 'd', mas d = %1.25f\n", d);
	printf("\tAtribuímos 0.2 a 'e', mas e = %1.25f\n", e);
	printf("\tf = d + e = %1.25f\n", f);
	printf("\tComparando 'f' com 0.3, obtemos %d\n", (f==0.3));
	f = 2.0*PI/3.0;
	printf("\tf = 2*PI/3 = %1.25f\n", f);
	return 0;
}
