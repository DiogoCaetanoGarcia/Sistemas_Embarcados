#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Imprime um caractere em stderr
void* print_xs (void* c)
{
	char *charactere = (char *) c;
	while (1) fputc(*charactere, stderr);
	return NULL;
}
int main ()
{
	pthread_t thread_id1;
	pthread_t thread_id2;
	char c1 = 'A';
	char c2 = 'B';
	printf("Serao criadas duas threads:\n");
	printf("   - A primeira ira chamar a funcao print_xs(),\n");
	printf("     para escrever continuamente 'A' na tela;\n");
	printf("   - A segunda ira chamar a funcao print_xs(),\n");
	printf("     que escreve continuamente 'B' na tela;\n");
	printf("Enquanto isso, o programa principal ira escrever\n");
	printf("continuamente '-' na tela.\n\n");
	printf("A diferenca deste exemplo para o anterior eh que\n");
	printf("neste a funcao print_xs() recebeu paramentos de entrada.\n");
	system("pause");
	pthread_create (&thread_id1, NULL, &print_xs, &c1);
	pthread_create (&thread_id2, NULL, &print_xs, &c2);
	// Imprime '-' continuamente em stderr
	while(1) fputc ('-', stderr);
	return 0;
}















