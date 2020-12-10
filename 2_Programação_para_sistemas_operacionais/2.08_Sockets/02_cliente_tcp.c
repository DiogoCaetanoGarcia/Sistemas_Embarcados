#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>

int main (int argc, char* const argv[])
{
	if(argc < 4)
	{
		puts("Modo de Uso:");
		printf("%s SERVER_IP SERVER_PORT MSG\n", argv[0]);
		exit(1);
	}
	int socket_id;
	struct sockaddr_in servidorAddr;
	int length;
	unsigned short servidorPorta;
	char *IP_Servidor;
	char *mensagem;
	IP_Servidor = argv[1];
	servidorPorta = atoi(argv[2]);
	mensagem = argv[3];

	socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&servidorAddr, 0, sizeof(servidorAddr));
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor);
	servidorAddr.sin_port = htons(servidorPorta);
	connect(socket_id, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr));
	length = strlen(mensagem) + 1;
	write(socket_id, &length, sizeof(length));
	write(socket_id, mensagem, length);
	close(socket_id);
	return 0;
}