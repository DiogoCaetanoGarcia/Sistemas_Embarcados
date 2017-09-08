#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int string_valida(char *str)
{
	char c = *str;
	while(c!='\0')
	{
		if((c<'0')||(c>'9'))
			return 0;
		c = *(++str);
	}
	return 1;
}

int main(int argc, const char * argv[])
{
	int fp;
	char *idade_end;
	char nome_arq[500];
	char conteudo[7800];
	if(argc<3)
	{
		puts("Insira um nome e uma idade!");
		return -1;
	}
	if(string_valida((char*)argv[2])==0)
	{
		puts("Insira uma idade inteira valida!");
		return -2;
	}
	sprintf(nome_arq, "%s.txt", argv[1]);
	sprintf(conteudo,
		"Nome: %s\nIdade: %s anos\n",
		argv[1], argv[2]);
	fp = open(nome_arq, O_WRONLY | O_CREAT, S_IRWXU);
	if(fp==-1)
	{
		printf ("Erro na abertura do arquivo.\n");
		exit (1);
	}
	write(fp, conteudo, strlen(conteudo)*sizeof(char));
	close(fp);
	
	return 0;
}