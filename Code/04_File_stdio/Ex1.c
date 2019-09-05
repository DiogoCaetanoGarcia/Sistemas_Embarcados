#include <stdio.h>

int main(int argc, const char * argv[])
{
	// Declaracao da estrutura
	FILE *fp;
	// O arquivo se chama
	// exemplo.bin e esta localizado
	// no diretório corrente
	fp = fopen("exemplo.bin","wb");
	// Mensagem de erro caso o
	// arquivo nao seja aberto
	if(!fp)
		printf("Erro na abertura do arquivo.");
	fclose(fp);
	return 0;
}