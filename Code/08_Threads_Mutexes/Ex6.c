#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg);

int main()
{
	pthread_t a_thread;
	void *thread_result;
	
	printf("Criando a thread\n");
	pthread_create(&a_thread, NULL, thread_function, NULL);
	sleep(5);
	printf("Cancelando a thread\n");
	pthread_cancel(a_thread);
	printf("Thread cancelada!\n");
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
	pthread_exit(0);
}