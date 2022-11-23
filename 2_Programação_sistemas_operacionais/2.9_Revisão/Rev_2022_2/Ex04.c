#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i;
	printf("Argumentos: ");
	for(i=1; i<argc; i++)
		printf("%s ", argv[i]);
	printf("\n");
	return 0;
}