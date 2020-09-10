#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

volatile int varCompartilhada=0;

void* incrementa_contador (void *arg)
{
	for (unsigned int i=0; i < 10000; i++)
	{
		varCompartilhada++;
	}
	return NULL;
}

void* decrementa_contador (void *arg)
{
	for (unsigned int i=0; i < 10000; i++)
	{
		varCompartilhada--;
	}
	return NULL;
}

int main (int argc, char** argv) {

	pthread_t t0;
	pthread_t t1;

	int res0, res1;
	printf("Valor inicial: %d\n", varCompartilhada);
	res0 = pthread_create(&t0, NULL, &incrementa_contador, NULL);
	res1 = pthread_create(&t1, NULL, &decrementa_contador, NULL);
	res0 = pthread_join(t0, NULL);
	res1 = pthread_join(t1, NULL);
	printf("Valor final: %d\n", varCompartilhada);
	return 0;
}