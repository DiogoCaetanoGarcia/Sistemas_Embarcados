#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 10000000

struct vetor_int
{
	int *x;
	int tam;
	double media;
};

void preencher_vetores(
	struct vetor_int *vx,
	struct vetor_int *vy);
void calc_media(
	struct vetor_int *v);
double distancia_euclidiana(
	struct vetor_int *v1,
	struct vetor_int *v2);

int main(int argc, char *argv[])
{
	struct vetor_int v1, v2;
	double dist_eucl;

	v1.x = (int *)malloc(N*sizeof(int));
	v1.tam = N;
	v2.x = (int *)malloc(N*sizeof(int));
	v2.tam = N;

	preencher_vetores(&v1, &v2);

	calc_media(&v1);
	calc_media(&v2);
	dist_eucl = distancia_euclidiana(&v1, &v2);

	printf("Resultado %s:\n", argv[0]);
	printf("   Media(x) = %1.10f\n",
		v1.media);
	printf("   Media(y) = %1.10f\n",
		v2.media);
	printf("   Dist_euclidiana(x,y) = %3.10f\n\n",
		dist_eucl);

	free(v1.x);
	free(v2.x);
	return 0;
}

void preencher_vetores(struct vetor_int *vx, struct vetor_int *vy)
{
	int i;
	for(i=0; i<(vx->tam); i++)
	{
		vx->x[i] = 1000/(i+1);
		vy->x[i] = 1000/(3*i*i+5*i+1);
	}
}

void calc_media(struct vetor_int *v)
{
	int i;
	for(v->media=0.0, i=0; i<(v->tam); i++)
		v->media += (double)v->x[i];
	v->media /= (double)v->tam;
}

double distancia_euclidiana(struct vetor_int *v1, struct vetor_int *v2)
{
	double dist_eucl, dummy;
	int i;

	for(dist_eucl=0.0, i=0; i<v1->tam; i++)
	{
		dummy = (double)v1->x[i];
		dummy -= (double)v2->x[i];
		dist_eucl += dummy*dummy;
	}
	return sqrt(dist_eucl);
}
