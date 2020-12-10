#include <stdio.h>	// Para a funcao printf()
#include <stdlib.h>	// Para a função exit()
#include <fcntl.h>	// Para a funcao open()
#include <unistd.h>	// Para a funcao close()

int main(int argc, const char * argv[])
{
	int fd = open("exemplo.bin", O_RDWR);
	if(fd==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(-1);
	}
	close(fd);

	return 0;
}
