#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* print_1(void* dummy_ptr);
void* print_2(void* dummy_ptr);

int main()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	
	printf("Pressione CONTROL+C para sair do programa\n\n");
	pthread_create(&thread_id1, NULL, &print_1, NULL);
	pthread_create(&thread_id2, NULL, &print_2, NULL);
	while(1)
	{
		fputc('-', stderr);
		usleep(50000);
	}
	return 0;
}

void* print_1(void* dummy_ptr)
{
	while(1)
	{
		fputc('1', stderr);
		usleep(50000);
	}
	return NULL;
}

void* print_2(void* dummy_ptr)
{
	while(1)
	{
		fputc('2', stderr);
		usleep(50000);
	}
	return NULL;
}