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
 
int main(int argc, char **argv)
{
	struct sockaddr_in servidorAddr;
	int socket_id;
	int port = 80;
	char *host, *ip, *get, *page, buf[BUFSIZ+1];
	FILE *fp;

	if(argc != 3)
	{
		fprintf(stderr, "Uso: %s host pagina\n", argv[0]);
		fprintf(stderr, "   host: o endereco do website. ex: www.unb.br\n");
		fprintf(stderr, "   pagina: a pagina para obter. ex: /\n");
		exit(2);
	}
	host = argv[1];
	page = argv[2];

	fprintf(stderr, "Abrindo o socket para o cliente... ");
	if((socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		fprintf(stderr, "Erro na criacao do socket!\n");
		exit(0);
	}
	fprintf(stderr, "Feito!\n");

	fprintf(stderr, "Obtendo o IP do servidor... ");
	ip = get_ip(host);
	fprintf(stderr, "Feito!\n");

	fprintf(stderr, "Conectando o socket ao IP %s pela porta %d... ", ip, port);
	memset(&servidorAddr, 0, sizeof(servidorAddr));
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(ip);
	servidorAddr.sin_port = htons(port);
	if(connect(socket_id, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0)
	{
		fprintf(stderr, "Erro na conexao!\n");
		exit(0);
	}
	fprintf(stderr, "Feito!\n");

	get = build_get_query(host, page);
	fprintf(stderr, "Pedido HTTP:\n\n");
	fprintf(stderr, "---------------------------------------\n");
	fprintf(stderr, "%s", get);
	fprintf(stderr, "---------------------------------------\n");
 
	fprintf(stderr, "Enviando o pedido HTTP ao servidor... ");
	write(socket_id, get, strlen(get));
	fprintf(stderr, "Feito!\n");

	free(get);
	free(ip);

	fprintf(stderr, "Recebendo o resultado HTML e o escrevendo no arquivo 'saida.html'... ");
	fp = fopen("saida.html","w");
	int tmpres;
	while((tmpres = read(socket_id, buf, BUFSIZ)) > 0)
	{
		buf[tmpres] = '\0';
		fprintf(fp, "%s", buf);
	}
	if(tmpres < 0)
		fprintf(stderr, "Erro no recebimento de dados!\n");
	fprintf(stderr, "Feito!\n");
	close(socket_id);
	fclose(fp);
	return 0;
}

char *build_get_query(char *host, char *page)
{
	char *query;
	char *getpage = page;
	char *tpl = "GET %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: HTMLGET 1.1\r\nAccept: */*\r\n\r\n";
	query = (char *)malloc(strlen(host)+strlen(getpage)+strlen(tpl));
	sprintf(query, tpl, getpage, host);
	return query;
}

char *get_ip(char *host)
{
	struct hostent *hent;
	int iplen = 15; //XXX.XXX.XXX.XXX
	char *ip = (char *)malloc(iplen+1);
	memset(ip, 0, iplen+1);
	if((hent = gethostbyname(host)) == NULL)
	{
		herror("Can't get IP");
		exit(1);
	}
	if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL)
	{
		perror("Can't resolve host");
		exit(1);
	}
	return ip;
}