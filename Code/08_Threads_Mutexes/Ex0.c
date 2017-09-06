#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* print_1(void)
{
	// Imprime '1' continuamente em stderr.
	while(1)
	{
		fputc('1', stderr);
		usleep(50000); // Atraso de 50000 us, ou 50 ms
	}
	return NULL;
}

void* print_2(void)
{
	// Imprime '2' continuamente em stderr.
	while(1)
	{
		fputc('2', stderr);
		usleep(50000);
	}
	return NULL;
}
int main ()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	printf("Serao criadas duas threads:\n");
	printf("   - A primeira ira chamar a funcao print_1(),\n");
	printf("     que escreve continuamente '1' na tela;\n");
	printf("   - A segunda ira chamar a funcao print_2(),\n");
	printf("     que escreve continuamente '2' na tela;\n");
	printf("Enquanto isso, o programa principal ira escrever\n");
	printf("continuamente '-' na tela.\n\n");
	printf("Repare na ordem com que os caracteres sao escritos.\n");
	printf("Percebe algum padrao?\n");
	system("pause");
	printf("Pressione CONTROL+C para sair do programa\n\n");
	pthread_create (&thread_id1, NULL, &print_1, NULL);
	// Cria um novo thread. A nova thread irá chamar a função print_2
	pthread_create (&thread_id2, NULL, &print_2, NULL);
	// Imprime '-' continuamente em stderr.
	while(1)
	{
		fputc('-', stderr);
		usleep(50000);
	}
	// fputc ('-', stderr);
	return 0;
}













