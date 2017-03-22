#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
	int fp;
	char c;

	fp = open ("exercicio5.txt", O_RDONLY);
	if(fp==-1)
	{
		printf ("Erro na abertura do arquivo.\n");
		exit (1);
	}
	while(read(fp, &c, 1) != 0)
		printf("%c", c);
	close(fp);
	
	return 0;
}