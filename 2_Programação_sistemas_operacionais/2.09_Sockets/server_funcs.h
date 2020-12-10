#ifndef SERVER_FUNCS_H
#define SERVER_FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

char socket_name[100];
int  socket_id;
int  print_client_message(int client_socket);
void end_server(int signum);

#endif // SERVER_FUNCS_H