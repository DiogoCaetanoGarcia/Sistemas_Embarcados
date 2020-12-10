all: 01_cliente_local.out 02_cliente_tcp.out 03_http_client.out 01_servidor_local.out 02_servidor_tcp.out
01_cliente_local.out: 01_cliente_local.c
	gcc 01_cliente_local.c -o 01_cliente_local.out
02_cliente_tcp.out:    02_cliente_tcp.c
	gcc 02_cliente_tcp.c   -o 02_cliente_tcp.out
03_http_client.out: 03_http_client.o client_funcs.o
	gcc 03_http_client.o client_funcs.o -o 03_http_client.out
01_servidor_local.out: 01_servidor_local.o server_funcs.o
	gcc 01_servidor_local.o server_funcs.o -o 01_servidor_local.out
02_servidor_tcp.out:   02_servidor_tcp.o server_funcs.o
	gcc 02_servidor_tcp.o   server_funcs.o -o 02_servidor_tcp.out
03_http_client.o:
	gcc -c 03_http_client.c
01_servidor_local.o:   01_servidor_local.c
	gcc -c 01_servidor_local.c
02_servidor_tcp.o:     02_servidor_tcp.c
	gcc -c 02_servidor_tcp.c
server_funcs.o:        server_funcs.c
	gcc -c server_funcs.c
client_funcs.o:
	gcc -c client_funcs.c
clean:
	rm -f *.out *.o *.bin *.txt *.html