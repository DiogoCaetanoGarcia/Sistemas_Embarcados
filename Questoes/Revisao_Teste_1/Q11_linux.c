#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

volatile int cnt=0;
static pthread_mutex_t mutexLock;

void *thread_function(void *arg)
{
	int i1=cnt;
	while(i1!=10)
	{
		while(i1==cnt);
		i1 = cnt;
		printf("%d\n", i1);
	}
	pthread_exit(0);
}

int main()
{
	int i;
	pthread_t a_thread;
	void *thread_result;
	pthread_create(&a_thread, NULL, thread_function, NULL);
	for(i=0; i<10; i++)
	{
		sleep(1);
		cnt++;
	}
	sleep(1);
	pthread_join(a_thread, NULL);
	return 0;
}