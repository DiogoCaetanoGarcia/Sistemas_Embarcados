#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* print_xs (void* c);
int main ()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	char c1 = 'A';
	char c2 = 'B';
	printf("Pressione CONTROL+C para sair do programa\n\n");
	pthread_create (&thread_id1, NULL, &print_xs, &c1);
	pthread_create (&thread_id2, NULL, &print_xs, &c2);
	while(1)
	{
		fputc('-', stderr);
		usleep(50000);
	}
	return 0;
}

void* print_xs (void* c)
{
	char *charactere = (char *) c;
	while (1)
	{
		fputc(*charactere, stderr);
		usleep(50000);
	}

	return NULL;
}