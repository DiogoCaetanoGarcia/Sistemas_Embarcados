#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
	int fd = open("exercicio2.txt",
		O_RDWR | O_CREAT);
	if(fd==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(-1);
	}
	printf("Abertura OK\n");
	close(fd);
	return 0;
}