#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
	float pi = 3.1415;
	float pilido;
	int fd = open ("exercicio7.txt",
		O_RDWR | O_CREAT, S_IRWXU);
	if(fd==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(-1);
	}
	write(fd, &pi, sizeof(float));
	close(fd);
	fd = open("exercicio7.txt",
		O_RDONLY);
	read(fd, &pilido, sizeof(float));
	close(fd);
	printf("\nO valor de PI (lido"
		" do arquivo) eh: %f\n\n",
		 pilido);
	return(0);
}