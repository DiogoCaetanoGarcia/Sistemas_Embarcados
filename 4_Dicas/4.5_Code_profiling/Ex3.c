#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 1000000

void preencher_vetores(
	int x[], int y[], int tam);
double calc_media1(
	int a[], int tam);
double calc_media2(
	int a[], int tam);
double distancia_euclidiana1(
	int a[], int b[], int len);
double distancia_euclidiana2(
	int a[], int b[], int len);
void check_diff(double a[2], char *s);


int main(int argc, char *argv[])
{
	int *x;
	int *y;
	double dist_eucl[2], media_x[2], media_y[2];

	x = (int *)malloc(N*sizeof(int));
	y = (int *)malloc(N*sizeof(int));

	preencher_vetores(x, y, N);

	media_x[0] = calc_media1(x, N);
	media_y[0] = calc_media1(y, N);
	dist_eucl[0] = distancia_euclidiana1(x, y, N);

	media_x[1] = calc_media2(x, N);
	media_y[1] = calc_media2(y, N);
	dist_eucl[1] = distancia_euclidiana2(x, y, N);

	check_diff(media_x, "media_x");
	check_diff(media_y, "media_y");
	check_diff(dist_eucl, "dist_eucl");

	// printf("Resultado %s:\n", argv[0]);
	// printf("   Media(x) = %1.10f\n",
	// 	media_x);
	// printf("   Media(y) = %1.10f\n",
	// 	media_y);
	// printf("   Dist_euclidiana(x,y) = %3.10f\n\n",
	// 	dist_eucl);

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

double calc_media1(int a[], int tam)
{
	int i;
	double media;
	for(media=0.0, i=0; i<tam; i++)
		media += ((double)a[i])/((double)tam);
	return media;
}

double calc_media2(int a[], int tam)
{
	int i;
	double media;
	for(media=0.0, i=0; i<tam; i++)
		media += (double)a[i];
	media /= (double)tam;
	return media;
}

double distancia_euclidiana1(int a[], int b[], int len)
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

double distancia_euclidiana2(int a[], int b[], int len)
{
	double dist_eucl, dummy;
	int i;

	for(dist_eucl=0.0, i=0; i<len; i++)
	{
		dummy = (double)a[i];
		dummy -= (double)b[i];
		dist_eucl += dummy*dummy;
	}
	return sqrt(dist_eucl);
}


void check_diff(double a[2], char *s)
{
	if(a[0] != a[1])
		printf("%s = (%f,%f), erro = %f\n",
			s, a[0], a[1], a[0]-a[1]);
}
