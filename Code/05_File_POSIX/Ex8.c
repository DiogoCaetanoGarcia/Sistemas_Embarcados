#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[])
{
	int fp;
	char str[100] = {'\0'};
	float pi = 3.1415;
	float pilido;

	fp = open ("exercicio8.txt",
		O_RDWR | O_CREAT, S_IRWXU);
	if(fp==-1)
	{
		printf("Erro na abertura"
			" do arquivo.\n");
		exit(1);
	}
	sprintf(str, "pi = %f\n", pi);
	write(fp, str, 100);
	close(fp);

	fp = open("exercicio8.txt",
		O_RDONLY);
	read(fp, str, 100);
	sscanf(str, "pi = %f\n", &pilido);
	close(fp);

	printf("\nO valor de PI (lido"
		" do arquivo) eh: %f\n\n",
		 pilido);
	return(0);
}