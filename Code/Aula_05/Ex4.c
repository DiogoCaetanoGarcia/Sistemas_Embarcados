#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
	int fp;
	
	fp = open("exercicio4.txt", O_RDWR | O_CREAT, S_IRWXU);
	if(fp==-1)
	{
		printf("Erro na abertura do arquivo.\n");
		exit(-1);
	}
	printf("\n");
	printf("Arquivo 'exercicio4.txt' criado. Detalhes:\n");
	system("ls -la exercicio4.txt");
	printf("Percebeu a diferenca na chamada de open()?\n");
	printf("\n");
	close(fp);

	return 0;
}
