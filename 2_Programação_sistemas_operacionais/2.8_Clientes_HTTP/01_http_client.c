#include "client_funcs.h"

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		fprintf(stderr, "Uso: %s host pagina\n", argv[0]);
		exit(-1);
	}
	struct sockaddr_in servidorAddr;
	int socket_id;
	int port = 80;
	char *host, *ip, *get, *page, buf[BUFSIZ+1];
	FILE *fp;

	host = argv[1];
	page = argv[2];
	get = build_get_query(host, page);
	fprintf(stderr, "Pedido HTTP:\n");
	fprintf(stderr, "---------------------------------------\n");
	fprintf(stderr, "%s", get);
	fprintf(stderr, "---------------------------------------\n");
	socket_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ip = get_ip(host);
	memset(&servidorAddr, 0, sizeof(servidorAddr));
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = inet_addr(ip);
	servidorAddr.sin_port = htons(port);
	if(connect(socket_id,
		(struct sockaddr *) &servidorAddr, 
		sizeof(servidorAddr)) < 0)
	{
		fprintf(stderr, "Erro na conexao!\n");
		exit(-4);
	}
	write(socket_id, get, strlen(get));
	free(get);
	free(ip);
	fprintf(stderr, "Recebendo o resultado HTML e o escrevendo no arquivo 'saida.html'...\n");
	fp = fopen("saida.html","w");
	int tmpres;
	while((tmpres = read(socket_id, buf, BUFSIZ)) > 0)
	{
		buf[tmpres] = '\0';
		fprintf(fp, "%s", buf);
	}
	if(tmpres < 0)
		fprintf(stderr, "Erro no recebimento de dados!\n");
	close(socket_id);
	fclose(fp);
	return 0;
}