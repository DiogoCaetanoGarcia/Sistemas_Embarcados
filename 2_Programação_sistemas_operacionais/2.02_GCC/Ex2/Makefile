mensagens: main.o mensagens.o
	gcc $(CFLAGS) -o mensagens.out main.o mensagens.o
main.o: main.c mensagens.h
	gcc $(CFLAGS) -c main.c
mensagens.o: mensagens.c mensagens.h
	gcc $(CFLAGS) -c mensagens.c
clean:
	rm -f *.o mensagens