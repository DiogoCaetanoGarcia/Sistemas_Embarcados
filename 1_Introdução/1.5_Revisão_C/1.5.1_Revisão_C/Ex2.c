#include <stdio.h>
//SOE(1) Definições não ocupam memória, simplesmente substituindo suas instâncias ao longo do texto
#define PI 3.14159265358979311599796346854419

int main(void)
{
	//SOE(1) Tudo que vem depois de // até o final da linha é ignorado pelo compilador
	// Comentario por linha
	char a = 115;
	//SOE(2) Tudo que vem entre  /* e */ é ignorado pelo compilador
	/* Comentario
	por bloco*/
	printf("Olá mundo!\n");
	printf("Mesmo valor, diferentes interpretações:\n");
	//SOE(1) A mesma variável 'a' é interpretada como número, 115, e como caracter ASCII, 's'
	printf("\ta = %d ('%c' em ASCII)\n", a, a);
	//SOE(1) A representação em ponto flutuante pode ser enganadora
	float d = 0.1, e = 0.2;
	double f = d+e;
	printf("Cuidado com a representação em ponto flutuante:\n");
	//SOE(1) Atribuímos 0.1 a 'd', mas d = 0.1000000014901161193847656
	printf("\tAtribuímos 0.1 a 'd', mas d = %1.25f\n", d);
	//SOE(1) Atribuímos 0.2 a 'e', mas e = 0.2000000029802322387695312
	printf("\tAtribuímos 0.2 a 'e', mas e = %1.25f\n", e);
	//SOE(1) f = d + e = 0.3000000119209289550781250
	printf("\tf = d + e = %1.25f\n", f);
	//SOE(1) 'f' e 0.3 são diferentes
	printf("\tComparando 'f' com 0.3, obtemos %d\n", (f==0.3));
	f = 2.0*PI/3.0;
	//SOE(1) f = 2*PI/3 = 2.0943951023931952626355724
	printf("\tf = 2*PI/3 = %1.25f\n", f);
	return 0;
}
