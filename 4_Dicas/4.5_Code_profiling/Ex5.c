#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define N 10000000

struct vetor_int
{
	int *x;
	int tam;
	double media;
};

struct dist_eucl_thread_params
{
	struct vetor_int v1, v2;
	double dist_eucl;
};

void* media_thread(void* parameters);
void* dist_eucl_thread(void* parameters);
void preencher_vetor(
	struct vetor_int *v);
void calc_media(
	struct vetor_int *v);
double distancia_euclidiana(
	struct vetor_int *v1,
	struct vetor_int *v2);
void run_media_thread(struct vetor_int* v, int num_threads);
double run_dist_eucl_thread(struct vetor_int* v1, struct vetor_int* v2, int num_threads);

int main(int argc, char *argv[])
{
	struct vetor_int v1, v2;
	double dist_eucl;
	v1.x = (int *)malloc(N*sizeof(int));
	v1.tam = N;
	v2.x = (int *)malloc(N*sizeof(int));
	v2.tam = N;

	// srandom(time(NULL));
	preencher_vetor(&v1);
	preencher_vetor(&v2);

	run_media_thread(&v1, 8);
	run_media_thread(&v2, 8);
	dist_eucl = run_dist_eucl_thread(&v1, &v2, 8);
	// dist_eucl = distancia_euclidiana(&v1, &v2);

	printf("Resultado %s:\n", argv[0]);
	printf("   Media(x) = %3.1f\n",
		v1.media);
	printf("   Media(y) = %3.1f\n",
		v2.media);
	printf("   Dist_euclidiana(x,y) = %3.1f\n\n",
		dist_eucl);

	free(v1.x);
	free(v2.x);
	return 0;
}

void preencher_vetor(struct vetor_int *v)
{
	int i;
	for(i=0; i<(v->tam); i++)
		v->x[i] = 100*((char)random())+5;
}

void* media_thread(void* parameters)
{
	struct vetor_int* p = (struct vetor_int*) parameters;
	calc_media(p);
	return NULL;
}

void* dist_eucl_thread(void* parameters)
{
	struct dist_eucl_thread_params* p = (struct dist_eucl_thread_params*) parameters;
	p->dist_eucl = distancia_euclidiana(
		&(p->v1), &(p->v2));
}

void run_media_thread(struct vetor_int* v, int num_threads)
{
	pthread_t *thread_id;
	struct vetor_int *media_args;
	int i, tam_interm;

	thread_id = (pthread_t *)malloc(sizeof(pthread_t)*num_threads);
	media_args = (struct vetor_int *)malloc(sizeof(struct vetor_int)*num_threads);

	tam_interm = (v->tam)/num_threads;
	for(i=0; i<num_threads; i++)
	{
		media_args[i].x = &(v->x[i*tam_interm]);
		media_args[i].tam = tam_interm;
		pthread_create(&thread_id[i],
			NULL, &media_thread,
			&media_args[i]);
	}
	for(i=0; i<num_threads; i++)
		pthread_join(thread_id[i], NULL);
	v->media = 0;
	for(i=0; i<num_threads; i++)
		v->media += media_args[i].media;
	v->media /= num_threads;
	free(thread_id);
	free(media_args);
}

double run_dist_eucl_thread(struct vetor_int* v1, struct vetor_int* v2, int num_threads)
{
	pthread_t *thread_id;
	struct dist_eucl_thread_params *de_args;
	int i, tam_interm;
	double dist_eucl;

	thread_id = (pthread_t *)malloc(sizeof(pthread_t)*num_threads);
	de_args = (struct dist_eucl_thread_params *)malloc(sizeof(struct dist_eucl_thread_params)*num_threads);

	tam_interm = (v1->tam)/num_threads;
	for(i=0; i<num_threads; i++)
	{
		de_args[i].v1.x = &(v1->x[i*tam_interm]);
		de_args[i].v1.tam = tam_interm;
		de_args[i].v2.x = &(v2->x[i*tam_interm]);
		de_args[i].v2.tam = tam_interm;
		pthread_create(&thread_id[i],
			NULL, &dist_eucl_thread,
			&de_args[i]);
	}
	for(i=0; i<num_threads; i++)
		pthread_join(thread_id[i], NULL);
	dist_eucl = 0;
	for(i=0; i<num_threads; i++)
		dist_eucl += de_args[i].dist_eucl*de_args[i].dist_eucl;
	dist_eucl = sqrt(dist_eucl);
	free(thread_id);
	free(de_args);
	return dist_eucl;
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
