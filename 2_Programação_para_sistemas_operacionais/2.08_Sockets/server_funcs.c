#include "server_funcs.h"

int print_client_message(int client_socket)
{
	int length, end_server_ok;
	char* text;
	read(client_socket, &length, sizeof(int));
	text = (char*) malloc(length);
	read(client_socket, text, length);
	fprintf(stderr,"Mensagem = %s\n", text);
	end_server_ok = !strcmp(text, "sair");
	free(text);
	return end_server_ok;
}

void end_server(int signum)
{
	fprintf(stderr,"Fechando servidor local\n");
	unlink(socket_name);
	close(socket_id);
	exit(0);
}