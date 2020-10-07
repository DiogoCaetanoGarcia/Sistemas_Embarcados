all: 01_http_client.out 02_http_client.out
01_http_client.out: 01_http_client.o client_funcs.o
	gcc 01_http_client.o client_funcs.o -o 01_http_client.out
02_http_client.out: 02_http_client.o client_funcs.o
	gcc 02_http_client.o client_funcs.o -o 02_http_client.out
01_http_client.o:
	gcc -c 01_http_client.c
02_http_client.o:
	gcc -c 02_http_client.c
client_funcs.o:
	gcc -c client_funcs.c
clean:
	rm -f *.out *.o *.bin *.txt *.html