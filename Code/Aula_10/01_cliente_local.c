#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main (int argc, char* const argv[])
{
	char *socket_name;
	char *mensagem;

	int socket_id;
	struct sockaddr name;
	int length;

	if (argc < 3)
	{
		puts("   Este programa cria um cliente que se comunica");
		puts("   a um servidor local no caminho especificado");
		puts("   pelo usuario. Para permitir que o cliente comunique-se");
		puts("   com este servidor, o servidor deve ser");
		puts("   executado inicialmente com um caminho definido,");
		puts("   e o cliente devera ser executado em outra");
		puts("   janela ou em outra aba do terminal, utilizando");
		puts("   o mesmo caminho. O servidor escreve na tela");
		puts("   todo texto enviado pelo cliente. Se o cliente");
		puts("   transmitir o texto \"sair\", o servidor se");
		puts("   encerra. Se o usuario pressionar CTRL-C para");
		puts("   o servidor, ele tambem se encerra.");
		puts("   encerra.");
		puts("   Modo de Uso:");
		printf("      %s <caminho_do_socket> <mensagem>\n", argv[0]);
		printf("   Exemplo: %s /tmp/socket1 \"Ola socket\"\n", argv[0]);
		exit(1);
	}
	socket_name = argv[1];
	mensagem = argv[2];

	fprintf(stderr, "Abrindo o socket local... ");
	socket_id = socket(PF_LOCAL, SOCK_STREAM,0);
	fprintf(stderr, "Feito!\n");

	fprintf(stderr, "Conectando o socket ao servidor no endereco local \"%s\"... ", socket_name);
	name.sa_family = AF_LOCAL;
	strcpy(name.sa_data, socket_name);
	connect(socket_id, &name, sizeof(name));
	fprintf(stderr, "Feito!\n");

	fprintf(stderr, "Mandando mensagem ao servidor... ");
	length = strlen(mensagem) + 1;
	write(socket_id, &length, sizeof(length));
	write(socket_id, mensagem, length);
	fprintf(stderr, "Feito!\n");

	fprintf(stderr, "Fechando o socket local... ");
	close(socket_id);
	fprintf(stderr, "Feito!\n");
	return 0;
}