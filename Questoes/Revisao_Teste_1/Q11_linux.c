#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

volatile int cnt=0;

void *thread_function(void *arg)
{
	int i = cnt;
	while(i!=10)
	{
		if(i!=cnt)
		{
			printf("cnt = %d\n", cnt);
			i = cnt;
		}
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
