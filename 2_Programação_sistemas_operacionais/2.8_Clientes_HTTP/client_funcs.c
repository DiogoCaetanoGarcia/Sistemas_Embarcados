#include "client_funcs.h"

char *build_get_query(char *host, char *page)
{
	char *query;
	char *getpage = page;
	query = (char *)malloc(strlen(host)+strlen(getpage)+100);
	sprintf(query,
		"GET %s HTTP/1.0\r\nHost: %s\r\nUser-Agent: HTMLGET 1.0\r\nAccept: */*\r\n\r\n",
		getpage,
		host);
	return query;
}

char *get_ip(char *host)
{
	struct hostent *hent;
	int iplen = 15; //XXX.XXX.XXX.XXX
	char *ip = (char *)malloc(iplen+1);
	memset(ip, 0, iplen+1);
	hent = gethostbyname(host);
	if(hent == NULL)
	{
		herror("Não foi possível obter o IP");
		exit(-2);
	}
	if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL)
	{
		perror("Can't resolve host");
		exit(-3);
	}
	return ip;
}
