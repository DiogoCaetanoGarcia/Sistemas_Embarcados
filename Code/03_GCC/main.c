#include <stdio.h>
#include <stdlib.h>
#include "reciprocal.h"

int main(int argc, char **argv)
{
	int i;
	if(argc<2)
	{
		printf(" --------------------------------\n");
		printf("| Insira um argumento de entrada |\n");
		printf("| na chamada deste programa.     |\n");
		printf("| Por exemplo:                   |\n");
		printf("|    $ ./reciprocal 2            |\n");
		printf("|         1/2 = 0.5              |\n");
		printf("|    $                           |\n");
		printf(" --------------------------------\n");
		return -1;
	}
	i = atoi(argv[1]);
	printf("   1/%d = %g\n", i, reciprocal(i));
	return 0;
}