#include "server_funcs.h"

int main (int argc, char* const argv[])
{
	if(argc < 2)
	{
		puts("Modo de Uso:");
		printf("%s NOME_SOCKET\n", argv[0]);
		exit(1);
	}
	struct sockaddr socket_struct;
	signal(SIGINT, end_server);
	strcpy(socket_name, argv[1]);
	//fprintf(stderr, "%s\n", socket_name);
	socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);
	socket_struct.sa_family = AF_LOCAL;
	strcpy(socket_struct.sa_data, socket_name);
	bind(socket_id, &socket_struct, sizeof(socket_struct));
	listen(socket_id, 10);
	while(1)
	{
		int socket_id_cliente, end_server_ok;
		struct sockaddr clienteAddr;
		socklen_t clienteLength = sizeof( (struct sockaddr *) &clienteAddr);

		socket_id_cliente = accept(socket_id, &clienteAddr, &clienteLength);
		end_server_ok = print_client_message(socket_id_cliente);
		close(socket_id_cliente);
		if(end_server_ok)
			end_server(0);
	}
	return 0;
}
