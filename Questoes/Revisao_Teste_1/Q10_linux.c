#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

volatile int cnt=0;
static pthread_mutex_t mutexLock;

void *thread_function(void *arg)
{
	int i;
	pthread_mutex_lock(&mutexLock);
	i = cnt;
	pthread_mutex_unlock(&mutexLock);
	while(i!=10)
	{
		pthread_mutex_lock(&mutexLock);
		if(i!=cnt)
		{
			printf("cnt = %d\n", cnt);
			i = cnt;
		}
		pthread_mutex_unlock(&mutexLock);
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
