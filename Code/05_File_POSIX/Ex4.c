#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
	int fd = open("exercicio4.txt",
		O_RDWR | O_CREAT, S_IRWXU);
	if(fd==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(-1);
	}
	system("ls -l exercicio3.txt "
		"exercicio4.txt");
	close(fd);
	return 0;
}