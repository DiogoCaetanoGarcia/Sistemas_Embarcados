all: Ex1.out Ex2.out Ex3.out Ex4.out Ex5.out Ex6.out Ex7.out Ex8.out
Ex1.out: Ex1.c
	gcc Ex1.c -o Ex1.out
Ex2.out: Ex2.c file_stdio.o
	gcc Ex2.c file_stdio.o -o Ex2.out
Ex3.out: Ex3.c
	gcc -std=c99 Ex3.c -o Ex3.out
Ex4.out: Ex4.c
	gcc Ex4.c -o Ex4.out
Ex5.out: Ex5.c file_stdio.o
	gcc -std=c99 file_stdio.o Ex5.c -o Ex5.out
Ex6.out: Ex6.c file_stdio.o
	gcc -std=c99 file_stdio.o Ex6.c -o Ex6.out
Ex7.out: Ex7.c file_stdio.o
	gcc Ex7.c file_stdio.o -o Ex7.out
Ex8.out: Ex8.c file_stdio.o
	gcc Ex8.c file_stdio.o -o Ex8.out
file_stdio.o:
	gcc -c file_stdio.c
clean:
	rm -f *.o *.out *.bin *.txt