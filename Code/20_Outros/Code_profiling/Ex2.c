#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10000000

void preencher_vetor(
	int a[], int tam);
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
	
	// srandom(time(NULL));
	preencher_vetor(x, N);
	media_x = calc_media(x, N);
	preencher_vetor(y, N);
	media_y = calc_media(y, N);
	dist_eucl = distancia_euclidiana(x, y, N);

	printf("Resultado %s:\n", argv[0]);
	printf("   Media(x) = %3.1f\n",
		media_x);
	printf("   Media(y) = %3.1f\n",
		media_y);
	printf("   Dist_euclidiana(x,y) = %3.1f\n\n",
		dist_eucl);

	free(x);
	free(y);
	return 0;
}

void preencher_vetor(int a[], int tam)
{
	int i;
	for(i=0; i<tam; i++)
		a[i] = 100*((char)random())+5;
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
