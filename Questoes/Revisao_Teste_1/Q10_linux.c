#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

volatile int cnt=0;
static pthread_mutex_t mutexLock;

void *thread_function(void *arg)
{
	int i1, i2;
	pthread_mutex_lock(&mutexLock);
	i2 = cnt;
	pthread_mutex_unlock(&mutexLock);
	while(i2!=10)
	{
		pthread_mutex_lock(&mutexLock);
		i1 = cnt;
		pthread_mutex_unlock(&mutexLock);
		do
		{
			pthread_mutex_lock(&mutexLock);
			i2 = cnt;
			pthread_mutex_unlock(&mutexLock);
		}while(i1==i2);
		printf("%d\n", i2);
	}
	pthread_exit(0);
}

int main()
{
	int i;
	pthread_t a_thread;
	void *thread_result;
	pthread_mutex_init(&mutexLock, NULL);
	pthread_create(&a_thread, NULL, thread_function, NULL);
	for(i=0; i<10; i++)
	{
		sleep(1);
		pthread_mutex_lock(&mutexLock);
		cnt++;
		pthread_mutex_unlock(&mutexLock);
	}
	sleep(1);
	pthread_join(a_thread, NULL);
	pthread_mutex_destroy(&mutexLock);
	return 0;
}