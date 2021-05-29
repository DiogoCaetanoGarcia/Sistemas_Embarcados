#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct char_print_parms
{
	char character;
	int count;
};

void* char_print (void* parameters)
{
	struct char_print_parms* p = (struct char_print_parms*) parameters;
	int i;
	for (i = 0; i < p->count; ++i)
		fputc(p->character, stderr);
	return NULL;
}

int main ()
{
	pthread_t thread1_id;
	struct char_print_parms thread1_args;
	thread1_args.character = 'X';
	thread1_args.count = 10;
	pthread_create (&thread1_id, NULL, &char_print, &thread1_args);
	pthread_t thread2_id;
	struct char_print_parms thread2_args;
	thread2_args.character = 'Y';
	thread2_args.count = 8;
	pthread_create (&thread2_id, NULL, &char_print, &thread2_args);
	pthread_join (thread1_id, NULL);
	pthread_join (thread2_id, NULL);
	fputs(" Terminando a execucao da thread principal.\n", stderr);
	return 0; 
}