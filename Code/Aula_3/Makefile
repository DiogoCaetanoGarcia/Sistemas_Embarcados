reciprocal: main.o reciprocal.o
	gcc $(CFLAGS) -o reciprocal main.o reciprocal.o
main.o: main.c reciprocal.h
	gcc $(CFLAGS) -c main.c
reciprocal.o: reciprocal.c reciprocal.h
	gcc $(CFLAGS) -c reciprocal.c
clean:
	rm -f *.o reciprocal