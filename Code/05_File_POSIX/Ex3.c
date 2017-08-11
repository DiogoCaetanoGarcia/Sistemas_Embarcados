#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
	int fp;
	
	fp = open("exercicio3.txt", O_RDWR | O_CREAT);
	if(fp==-1)
	{
		printf("Erro na abertura do arquivo.\n");
		exit(-1);
	}
	printf("\n");
	printf("Arquivo 'exercicio3.txt' criado. Detalhes:\n");
	system("ls -la exercicio3.txt");
	printf("\n");
	close(fp);

	return 0;
}