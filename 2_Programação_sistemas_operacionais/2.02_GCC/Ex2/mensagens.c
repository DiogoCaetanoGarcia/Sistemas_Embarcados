#include "mensagens.h"

void ola(char *hospede)
{
	msg("Hello", hospede);
}

void tchau(char *hospede)
{
	msg("Adios", hospede);
}

void msg(char *saudacao, char *hospede)
{
	printf("%s, %s!\n",
		saudacao,
		hospede);
}
