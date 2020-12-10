#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
	char str[100] = {'\0'};
	float pi = 3.1415;
	float pilido;
	int fd = open ("exercicio8.txt",
		O_RDWR | O_CREAT, S_IRWXU);
	sprintf(str, "pi = %f\n", pi);
	write(fd, str, 100);
	close(fd);

	fd = open("exercicio8.txt", O_RDONLY);
	read(fd, str, 100);
	sscanf(str, "pi = %f\n", &pilido);
	close(fd);
	printf("\nO valor de PI (lido"
		" do arquivo) eh: %f\n\n",
		 pilido);
	return(0);
}