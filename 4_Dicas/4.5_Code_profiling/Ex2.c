#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10000000

void preencher_vetores(
	int x[], int y[], int tam);
double calc_media(
	int a[], int tam);
double distancia_euclidiana(
	int a[], int b[], int len);

int main(int argc, char *argv[])
{
	int *x;
	int *y;
	double dist_eucl, media_x, media_y;

	x = (int *)malloc(N*sizeof(int));
	y = (int *)malloc(N*sizeof(int));

	preencher_vetores(x, y, N);
	media_x = calc_media(x, N);
	media_y = calc_media(y, N);
	dist_eucl = distancia_euclidiana(x, y, N);

	printf("Resultado %s:\n", argv[0]);
	printf("   Media(x) = %1.10f\n",
		media_x);
	printf("   Media(y) = %1.10f\n",
		media_y);
	printf("   Dist_euclidiana(x,y) = %3.10f\n\n",
		dist_eucl);

	free(x);
	free(y);
	return 0;
}

void preencher_vetores(int x[], int y[], int tam)
{
	int i;
	for(i=0; i<tam; i++)
	{
		x[i] = 1000/(i+1);
		y[i] = 1000/(3*i*i+5*i+1);
	}
}

double calc_media(int a[], int tam)
{
	int i;
	double media;
	for(media=0.0, i=0; i<tam; i++)
		media += ((double)a[i])/((double)tam);
	return media;
}

double distancia_euclidiana(int a[], int b[], int len)
{
	double dist_eucl;
	int i;

	for(dist_eucl=0.0, i=0; i<len; i++)
	{
		dist_eucl += (((double)a[i])-((double)b[i]))*
			(((double)a[i])-((double)b[i]));
	}
	return sqrt(dist_eucl);
}
