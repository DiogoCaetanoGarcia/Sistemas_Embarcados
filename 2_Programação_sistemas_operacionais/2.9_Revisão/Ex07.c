#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	char *arq, *chave = argv[1];
	int tamanho_arq, i_arq, i_chave, cont;
	int fd;
	fd = open(argv[2], O_RDONLY);
	tamanho_arq = lseek(fd, 0, SEEK_END);
	arq = (char*)malloc(tamanho_arq);
	lseek(fd, 0, SEEK_SET);
	read(fd, arq, tamanho_arq);
	close(fd);
	for(cont=i_chave=i_arq=0; i_arq<tamanho_arq; i_arq++)
	{
		if(arq[i_arq]==chave[i_chave])
		{
			i_chave++;
			if(chave[i_chave]=='\0')
			{
				cont++;
				i_chave=0;
			}
		}
		else
		{
			i_chave=0;
		}
	}
	printf("'%s' ocorre %d vezes no arquivo '%s'.\n",
		chave, cont, argv[2]);
	free(arq);
	return 0;
}