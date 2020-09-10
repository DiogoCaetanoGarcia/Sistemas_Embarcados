#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

volatile int varCompartilhada=0;
static pthread_mutex_t mutexLock;

void* incrementa_contador (void *arg)
{
	for (unsigned int i=0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutexLock);
		varCompartilhada++;
		pthread_mutex_unlock(&mutexLock);
	}
	return NULL;
}

void* decrementa_contador (void *arg)
{
	for (unsigned int i=0; i < 10000; i++)
	{
		pthread_mutex_lock(&mutexLock);
		varCompartilhada--;
		pthread_mutex_unlock(&mutexLock);
	}
	return NULL;
}

int main (int argc, char** argv)
{
	pthread_t t0;
	pthread_t t1;

	printf("Valor inicial: %d\n", varCompartilhada);	
	pthread_mutex_init(&mutexLock, NULL);
	pthread_create(&t0, NULL, incrementa_contador, NULL);
	pthread_create(&t1, NULL, decrementa_contador, NULL);
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);
	pthread_mutex_destroy(&mutexLock);
	printf("Valor final: %d\n", varCompartilhada);
	return 0;
}





















