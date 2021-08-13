#include "server_funcs.h"

int main (int argc, char* const argv[])
{
	if(argc < 2)
	{
		puts("Modo de Uso:");
		printf("%s PORT_NUM\n", argv[0]);
		exit(1);
	}
	unsigned short servidorPorta;
	struct sockaddr_in servidorAddr;
	servidorPorta = atoi(argv[1]);
	signal(SIGINT, end_server);
	socket_id = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&servidorAddr, 0, sizeof(servidorAddr));
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta);
	bind(socket_id, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr));
	listen(socket_id, 10);
	while(1)
	{
		int socketCliente, end_server_ok;
		struct sockaddr_in clienteAddr;
		unsigned int clienteLength = sizeof( (struct sockaddr *) &clienteAddr);

		socketCliente = accept(socket_id, (struct sockaddr *) &clienteAddr, &clienteLength);		
		fprintf(stderr, "Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
		end_server_ok = print_client_message(socketCliente);
		close(socketCliente);
		if(end_server_ok)
			end_server(0);
	}
	return 0;
}
