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
	pthread_t thread2_id;
	struct char_print_parms thread1_args;
	struct char_print_parms thread2_args;
	printf("Este exemplo eh igual ao anterior, exceto pelo uso da funcao pthread_join()\n");
	printf("antes de o programa principal terminar sua execucao em seguida.\n\n");
	printf("O que acontece com as threads?\n");
	system("pause");
	thread1_args.character = 'X';
	thread1_args.count = 20000;
	pthread_create (&thread1_id, NULL, &char_print, &thread1_args);
	thread2_args.character = 'Y';
	thread2_args.count = 10000;
	pthread_create (&thread2_id, NULL, &char_print, &thread2_args);
	pthread_join (thread1_id, NULL);
	pthread_join (thread2_id, NULL);
	fputs("\n**********************************************\n", stderr);
	fputs("* Terminou a execucao do programa principal. *\n", stderr);
	fputs("**********************************************\n", stderr);
	return 0; 
}






















