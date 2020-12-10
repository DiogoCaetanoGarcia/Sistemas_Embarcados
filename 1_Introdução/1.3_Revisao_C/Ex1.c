#include <stdio.h>

void msg_fixa();
void msg(char *str);
int soma_ponderada1(int a, int b);
int soma_ponderada2(int a, int b);
int soma_ponderada3(int *a, int *b);
int soma_ponderada4(int *a, int *b);
void somas_ponderadas(int a, int b, int *soma1, int *soma2);

int main(void)
{
	int x, y, z, w;

	msg_fixa();
	msg("Olá!");
	x = 3;
	y = 5;
	z = soma_ponderada1(x, y);
	printf("x = %d, y = %d, z = %d\n", x, y, z);

	x = 3;
	y = 5;
	z = soma_ponderada2(x, y);
	printf("x = %d, y = %d, z = %d\n", x, y, z);

	x = 3;
	y = 5;
	z = soma_ponderada3(&x, &y);
	printf("x = %d, y = %d, z = %d\n", x, y, z);

	x = 3;
	y = 5;
	z = soma_ponderada4(&x, &y);
	printf("x = %d, y = %d, z = %d\n", x, y, z);
	
	x = 3;
	y = 5;
	somas_ponderadas(x, y, &z, &w);
	printf("x = %d, y = %d, z = %d, w = %d\n", x, y, z, w);
	return 0;
}

void msg_fixa()
{
	printf("------------\n");
	printf("| MENSAGEM |\n");
	printf("------------\n");
}

void msg(char *str)
{
	printf("\nMENSAGEM = %s\n\n", str);
}

int soma_ponderada1(int a, int b)
{
	int c;
	c = (a + b + b)/3;
	return c;
}

int soma_ponderada2(int a, int b)
{
	int c;
	c = (a + b + b)/3;
	a++;
	return c;
}

int soma_ponderada3(int *a, int *b)
{
	int c;
	c = ((*a) + (*b) + (*b))/3;
	return c;
}

int soma_ponderada4(int *a, int *b)
{
	int c;
	c = ((*a) + (*b) + (*b))/3;
	(*a)++;
	return c;
}

void somas_ponderadas(int a, int b, int *soma1, int *soma2)
{
	*soma1 = (a + b + b)/3;
	*soma2 = (a + a + b)/3;
}
