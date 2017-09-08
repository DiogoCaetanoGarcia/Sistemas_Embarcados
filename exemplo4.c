#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100000

struct vector_calcs
{
	int *v;
	int N;
	long int soma;
};

void* calc_media_local(void* parameters)
{
	struct vector_calcs* p = (struct vector_calcs*) parameters;
	int i;
	p->soma = 0;
	for(i = 0; i < p->N; ++i)
		p->soma += (long int)p->v[i];
	return NULL;
}

int main ()
{

	pthread_t threads[4];
	struct vector_calcs vecs[4];
	int v[TAM];
	int i, medias[2];
	long int soma;
	
	// Preenche o vetor
	srand(time(NULL));
	for(i=0; i<TAM; i++)
		v[i] = rand()%1000;

	// Calcula a media de forma serial
	system("date +%s%3N");
	for(soma=0,i=0; i<TAM; i++)
		soma += (long int)v[i];
	soma /= TAM;
	medias[0] = (int)soma;
	system("date +%s%3N");

	// Calcula a media de forma paralela
	system("date +%s%3N");
	for(i=0; i<4; i++)
	{
		vecs[i].v = &(v[i*(TAM/4)]);
		vecs[i].N = (TAM/4);
		vecs[i].soma = 0;
		pthread_create(&(threads[i]), NULL, &calc_media_local, &(vecs[i]));
	}
	medias[1] = 0;
	for(i=0; i<4; i++)
	{
		pthread_join(threads[i], NULL);
		medias[1] += vecs[i].soma;
	}
	medias[1] /= TAM;
	system("date +%s%3N");

	printf("Medias = %d, %d\n", medias[0], medias[1]);
	return 0; 
}






















