#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE *fp;
	char string[100];
	if((fp = fopen("arquivo.txt","w")) ==NULL)
	{
		printf("\nNao consigo abrir o arquivo!");
		exit(1);
	}
	do
	{
		printf("\nDigite uma nova string."
			" Para terminar, digite <enter>: ");
		gets(string);
		fputs(string, fp);
		putc('\n', fp);
		if(ferror(fp))
		{
			perror("Erro na gravacao");
			fclose(fp);
			exit(1);
		}
	} while(strlen(string) > 0);
	fclose(fp);
}