#include <stdio.h>
#include <stdlib.h>
#include "mensagens.h"

int main(int argc, char **argv)
{
	if(argc<2) return -1;
	ola(argv[1]);
	tchau(argv[1]);
	return 0;
}