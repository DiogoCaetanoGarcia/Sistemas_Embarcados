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
	printf("Serao criadas duas threads. Ambas irao chamar a funcao\n");
	printf("char_print(), que escreve um caracter na tela N vezes.\n");
	printf("\n");
	printf("   ***************************************************************\n");
	printf("   * A funcao que cria threads, pthread_create(), aceita         *\n");
	printf("   * funcoes que tenham somente um parametro void* como entrada. *\n");
	printf("   * Para conseguir passar mais de um parametro de entrada,      *\n");
	printf("   * precisamos usar uma estrutura.                              *\n");
	printf("   ***************************************************************\n");
	printf("\n");
	printf("O programa principal ira terminar sua execucao em seguida.\n");
	printf("O que acontece com as threads?\n");
	system("pause");

	thread1_args.character = 'x';
	thread1_args.count = 100;
	pthread_create(&thread1_id, NULL, &char_print, &thread1_args);
	thread2_args.character = 'o';
	thread2_args.count = 80;
	pthread_create(&thread2_id, NULL, &char_print, &thread2_args);
	fputs("\n**********************************************\n", stderr);
	fputs("* Terminou a execucao do programa principal. *\n", stderr);
	fputs("**********************************************\n", stderr);
	return 0;
}









