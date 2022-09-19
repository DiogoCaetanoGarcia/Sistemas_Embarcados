#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[])
{
	FILE *fp;
	int c;
	fp = fopen("arquivo.txt","r");
	if(!fp)
	{
		printf( "Erro na abertura do arquivo");
		exit(-1);
	}
	c = getc(fp);
	while( c != EOF )
	{
		printf("%c", c);
		c = getc(fp);
	}
	fclose(fp);
	return 0;
}
