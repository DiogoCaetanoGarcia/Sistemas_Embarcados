all: Ex1.out Ex2.out Ex3.out Ex4.out Ex5.out Ex6.out Ex7.out
Ex1.out: Ex1.c
	gcc $(CFLAGS) Ex1.c -o Ex1.out -lm -lpthread 
Ex2.out: Ex2.c
	gcc $(CFLAGS) Ex2.c -o Ex2.out -lm -lpthread
Ex3.out: Ex3.c
	gcc $(CFLAGS) Ex3.c -o Ex3.out -lm -lpthread
Ex4.out: Ex4.c
	gcc $(CFLAGS) Ex4.c -o Ex4.out -lm -lpthread
Ex5.out: Ex5.c
	gcc $(CFLAGS) Ex5.c -o Ex5.out -lm -lpthread
Ex6.out: Ex6.c
	gcc $(CFLAGS) Ex6.c -o Ex6.out
Ex7.out: Ex7.c
	gcc $(CFLAGS) Ex7.c -o Ex7.out
clean:
	rm -f *.out *.bin *.txt