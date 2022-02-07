#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg);

int main()
{
	pthread_t a_thread;
	int j;

	printf("Criando a thread\n");
	pthread_create(&a_thread, NULL, thread_function, NULL);
	pthread_join(a_thread, (void*)&j);
	printf("j = %d\n", j);
	return 0;
}

void *thread_function(void *arg)
{
	int i;
	printf("Nova thread\n");
	for (i = 10; i > 0; i--)
	{
		printf("Faltam %2d segundos para acabar a thread ... \n", i);
		sleep(1);
	}
	pthread_exit((void *)i);
}