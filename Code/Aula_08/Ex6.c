#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void *thread_function(void *arg);
int main()
{
	pthread_t a_thread;
	void *thread_result;
	printf("Este exemplo mostra o cancelamento de threads.\n");
	printf("A thread criada faz uma contagem regressiva\n");
	printf("de 10 segundos para terminar sua execucao.\n");
	printf("O programa principal hiberna por 5 segundos,\n");
	printf("e cancela a thread criada.\n");
	system("pause");
	printf("********************\n");
	printf("* Criando a thread *\n");
	printf("********************\n");
	pthread_create(&a_thread, NULL, thread_function, NULL);
	sleep(5);
	printf("***********************\n");
	printf("* Cancelando a thread *\n");
	printf("***********************\n");
	pthread_cancel(a_thread);
	printf("*********************\n");
	printf("* Thread cancelada! *\n");
	printf("*********************\n");
	return 0;
}

void *thread_function(void *arg)
{
	int i;
	printf("*****************************\n");
	printf("* Função thread executando. *\n");
	printf("*****************************\n");
	for (i = 10; i > 0; i--)
	{
		printf("Faltam %2d segundos para acabar a thread ... \n", i);
		sleep(1);
	}
	pthread_exit(0);
}





























