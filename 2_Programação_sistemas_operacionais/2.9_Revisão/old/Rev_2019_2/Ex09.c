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
	long int v[N], v_max, v_max_parallel, v_max_threads[4];
	int i;
	struct max_thread_parms mtp[4];
	pthread_t thread_ids[4];

	srandom(time(NULL));
	for(i=0; i<N; i++)
	{
		v[i] = random();
	}

	v_max = max_vetor(v, N);
	printf("max(v[]) = %ld\n", v_max);

	for(i=0; i<4; i++)
	{
		mtp[i].v_int = &(v[i*N/4]);
		mtp[i].tam   = N/4;
		pthread_create(&thread_ids[i], NULL, &max_thread, &mtp[i]);
	}

	for(i=0; i<4; i++)
	{
		pthread_join(thread_ids[i], NULL);
		v_max_threads[i] = mtp[i].v_max_int;
	}
	
	v_max_parallel = max_vetor(v_max_threads, 4);

	if(v_max != v_max_parallel)
		printf("Houve erro no cálculo paralelizado do valor máximo!\n");
	else
		printf("Cálculo paralelizado do valor máximo foi OK!\n");
	return 0;
}