#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
	int fd = open("exercicio3.txt",
		O_RDWR | O_CREAT);
	if(fd==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(-1);
	}
	printf("Arquivo 'exercicio3.txt'"
		" criado. Detalhes:\n");
	system("ls -l exercicio3.txt");
	close(fd);
	return 0;
}