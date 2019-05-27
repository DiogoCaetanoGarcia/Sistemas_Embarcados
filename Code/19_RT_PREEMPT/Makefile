all: Ex1.o Ex2.o Ex3.o Ex4.o rt_lib.o eatmem.out
	gcc $(CFLAGS) -o Ex1.out Ex1.o rt_lib.o -lm
	gcc $(CFLAGS) -o Ex2.out Ex2.o rt_lib.o -lm
	gcc $(CFLAGS) -o Ex3.out Ex3.o rt_lib.o -lm
	gcc $(CFLAGS) -o Ex4.out Ex4.o rt_lib.o -lm
Ex1.o: Ex1.c rt_lib.h
	gcc $(CFLAGS) -c Ex1.c -lm
Ex2.o: Ex2.c rt_lib.h
	gcc $(CFLAGS) -c Ex2.c -lm
Ex3.o: Ex3.c rt_lib.h
	gcc $(CFLAGS) -c Ex3.c -lm
Ex4.o: Ex3.c rt_lib.h
	gcc $(CFLAGS) -c Ex4.c -lm
rt_lib.o: rt_lib.c rt_lib.h
	gcc $(CFLAGS) -c rt_lib.c -lm
eatmem.out: eatmem.c
	gcc $(CFLAGS) -o eatmem.out eatmem.c
clean:
	rm -f *.o *.out
