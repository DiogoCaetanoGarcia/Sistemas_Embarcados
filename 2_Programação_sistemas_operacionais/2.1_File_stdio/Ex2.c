#include <stdio.h>
#include <stdlib.h>
#include "file_stdio.h"

int main(int argc, const char * argv[])
{
	FILE *fp;
	fp = fopen("exemplo.bin","wb");
	erro_fopen(fp);
	printf("Arquivo aberto com sucesso.\n");
	fclose(fp);
	return 0;
}