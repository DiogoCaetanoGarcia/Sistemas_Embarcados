all: Ex1.o Ex2.o Ex3.o Ex4.o rt_lib.o
	gcc $(CFLAGS) -o Ex1.out Ex1.o rt_lib.o
	gcc $(CFLAGS) -o Ex2.out Ex2.o rt_lib.o
	gcc $(CFLAGS) -o Ex3.out Ex3.o rt_lib.o
	gcc $(CFLAGS) -o Ex4.out Ex4.o rt_lib.o
Ex1.o: Ex1.c rt_lib.h
	gcc $(CFLAGS) -c Ex1.c
Ex2.o: Ex2.c rt_lib.h
	gcc $(CFLAGS) -c Ex2.c
Ex3.o: Ex3.c rt_lib.h
	gcc $(CFLAGS) -c Ex3.c
Ex4.o: Ex3.c rt_lib.h
	gcc $(CFLAGS) -c Ex4.c
rt_lib.o: rt_lib.c rt_lib.h
	gcc $(CFLAGS) -c rt_lib.c
clean:
	rm -f *.o *.out