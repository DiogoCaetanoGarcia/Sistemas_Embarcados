#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
	char string[100];
	int i, fd = open ("exercicio5.txt", O_WRONLY | O_CREAT, S_IRWXU);
	if(fd==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(-1);
	}
	printf("Entre com a string a ser gravada no arquivo: ");
	gets(string);
	for(i=0; string[i] != '\0'; i++)
		write(fd, &(string[i]), 1);
	write(fd, "\n", 1);
	close(fd);
	return 0;
}