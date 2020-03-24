#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
	char c;
	int fd = open("exercicio5.txt", O_RDONLY);
	if(fd==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(1);
	}
	while(read(fd, &c, 1) != 0)
		printf("%c", c);
	close(fd);
	return 0;
}