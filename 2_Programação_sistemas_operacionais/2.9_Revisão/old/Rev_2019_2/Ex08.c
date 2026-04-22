#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define N 50000

long int max_vetor(long int *v, int tam)
{
	long int v_max;
	int i;
	for(v_max=v[0], i=1; i<tam; i++)
	{
		if(v[i] > v_max)
		{
			v_max = v[i];
		}
	}
	return v_max;
}

struct max_thread_parms
{
	long int *v_int;
	long int v_max_int;
	int tam; 
};

void* max_thread(void* parameters)
{
	struct max_thread_parms* p = (struct max_thread_parms*) parameters;
	p->v_max_int = max_vetor(p->v_int, p->tam);
	return NULL;
}

int main(void)
{
	long int v[N], v_max, v_max_threads;
	int i;
	struct max_thread_parms mtp0, mtp1, mtp2, mtp3;
	pthread_t thread0_id, thread1_id, thread2_id, thread3_id;

	srandom(time(NULL));
	for(i=0; i<N; i++)
	{
		v[i] = random();
	}

	v_max = max_vetor(v, N);
	printf("max(v[]) = %ld\n", v_max);

	mtp0.v_int = &(v[0*N/4]); // Endereço de v[0] 
	mtp0.tam   = N/4;         // Percorrer 12500 posições
	mtp1.v_int = &(v[1*N/4]); // Endereço de v[12500]
	mtp1.tam   = N/4;         // Percorrer 12500 posições
	mtp2.v_int = &(v[2*N/4]); // Endereço de v[25000]
	mtp2.tam   = N/4;         // Percorrer 12500 posições
	mtp3.v_int = &(v[3*N/4]); // Endereço de v[37500]
	mtp3.tam   = N/4;         // Percorrer 12500 posições

	pthread_create(&thread0_id, NULL, &max_thread, &mtp0);
	pthread_create(&thread1_id, NULL, &max_thread, &mtp1);
	pthread_create(&thread2_id, NULL, &max_thread, &mtp2);
	pthread_create(&thread3_id, NULL, &max_thread, &mtp3);

	pthread_join(thread0_id, NULL);
	pthread_join(thread1_id, NULL);
	pthread_join(thread2_id, NULL);
	pthread_join(thread3_id, NULL);
	
	v_max_threads = mtp0.v_max_int;
	if(mtp1.v_max_int > v_max_threads)
		v_max_threads = mtp1.v_max_int;
	if(mtp2.v_max_int > v_max_threads)
		v_max_threads = mtp2.v_max_int;
	if(mtp3.v_max_int > v_max_threads)
		v_max_threads = mtp3.v_max_int;

	if(v_max != v_max_threads)
		printf("Houve erro no cálculo paralelizado do valor máximo!\n");
	else
		printf("Cálculo paralelizado do valor máximo foi OK!\n");
	return 0;
}