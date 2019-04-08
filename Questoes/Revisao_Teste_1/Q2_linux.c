#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char chamada[50];
	char *chamada_date[] = {"date -d 01/01/%s +\"%%A\"", 
		"date -d 05/01/%s +\"%%A\"",
		"date -d 12/25/%s +\"%%A\""};
	char *texto_saida[] = {"   Ano Novo: ",
		"   Dia do trabalhador: ",
		"   Natal: "};
	int i, N=3;

	if(argc==2)
	{
		for(i=0; i<N; i++)
		{
			sprintf(chamada, chamada_date[i], argv[1]);
			fprintf(stderr, texto_saida[i]);
			system(chamada);	
		}
	}
	return 0;
}