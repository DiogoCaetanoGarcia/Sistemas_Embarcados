#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
	int fp;
	float pi = 3.1415;
   float pilido;

	fp = open ("exercicio7.txt", O_RDWR | O_CREAT, S_IRWXU);
	if(fp==-1)
	{
		printf ("Erro na abertura do arquivo.\n");
		exit (1);
	}
	write(fp, &pi, sizeof(float));
	close(fp);

	fp = open ("exercicio7.txt", O_RDONLY);
	read(fp, &pilido, sizeof(float));
	close(fp);

	printf("\nO valor de PI (lido do arquivo) eh: %f\n\n", pilido);
	return(0);
}