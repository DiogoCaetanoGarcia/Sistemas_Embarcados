#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>

int main (int argc, char* const argv[])
{
	int socket_id;
	struct sockaddr_in servidorAddr;
	int length;
	unsigned short servidorPorta;
	char *IP_Servidor;
	char *mensagem;

	if (argc != 4)
	{
		puts("   Este programa cria um cliente que se comunica");
		puts("   a um servidor TCP/IP na porta especificada");
		puts("   pelo usuario. Para permitir que o cliente comunique-se");
		puts("   com este servidor, o servidor deve ser");
		puts("   executado inicialmente com uma porta definida,");
		puts("   e o cliente devera ser executado em outra");
		puts("   janela ou em outra aba do terminal, utilizando");
		puts("   a mesma porta. O servidor escreve na tela");
		puts("   todo texto enviado pelo cliente. Se o cliente");
		puts("   transmitir o texto \"sair\", o servidor se");
		puts("   encerra. Se o usuario pressionar CTRL-C para");
		puts("   o servidor, ele tambem se encerra.");
		puts("   encerra.");
		puts("   Modo de Uso:");
		printf("      %s <IP do Servidor> <Porta do servidor> <Mensagem>\n", argv[0]);
		printf("   Exemplo: %s 127.0.0.1 8000 \"Ola socket\"\n", argv[0]);
		exit(1);
	}
	IP_Servidor = argv[1];
	servidorPorta = atoi(argv[2]);
	mensagem = argv[3];

	fprintf(stderr, "Abrindo o socket para o cliente... ");
	socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(socket_id < 0)
	{
		fprintf(stderr, "Erro na criacao do socket!\n");
		exit(0);
	}
	fprintf(stderr, "Feito!\n");
	
	fprintf(stderr, "Conectando o socket ao IP %s pela porta %d... ", IP_Servidor, servidorPorta);
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);
	if(connect(socket_id, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
	{
		fprintf(stderr, "Erro na conexao!\n");
		exit(0);
	}
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