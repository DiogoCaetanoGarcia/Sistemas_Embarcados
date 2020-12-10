#ifndef CLIENT_FUNCS_H
#define CLIENT_FUNCS_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

char *build_get_query(char *host, char *page);
char *get_ip(char *host);

#endif // CLIENT_FUNCS_H