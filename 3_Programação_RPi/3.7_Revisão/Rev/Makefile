all: Ex01.out Ex02.out Ex03.out Ex04.out Ex05.out Ex06.out Ex07.out Ex08.out Ex09.out Ex10.out
Ex01.out: Ex01.c gpiod_lib.o
	gcc Ex01.c gpiod_lib.o -o Ex01.out $(shell pkg-config --libs libgpiod) -lpthread
Ex02.out: Ex02.c gpiod_lib.o
	gcc Ex02.c gpiod_lib.o -o Ex02.out $(shell pkg-config --libs libgpiod) -lpthread
Ex03.out: Ex03.c gpiod_lib.o
	gcc Ex03.c gpiod_lib.o -o Ex03.out $(shell pkg-config --libs libgpiod) -lpthread
Ex04.out: Ex04.c
	gcc Ex04.c -o Ex04.out -lwiringPi
Ex05.out: Ex05.c
	gcc Ex05.c -o Ex05.out -lwiringPi
Ex06.out: Ex06.c
	gcc Ex06.c -o Ex06.out -lwiringPi
Ex07.out: Ex07.c
	gcc Ex07.c -o Ex07.out -lwiringPi
Ex08.out: Ex08.c
	gcc Ex08.c -o Ex08.out -lwiringPi
Ex09.out: Ex09.c gpiod_lib.o
	gcc Ex09.c gpiod_lib.o -o Ex09.out $(shell pkg-config --libs libgpiod) -lpthread
Ex10.out: Ex10.c gpiod_lib.o
	gcc Ex10.c gpiod_lib.o -o Ex10.out $(shell pkg-config --libs libgpiod) -lpthread
gpiod_lib.o: gpiod_lib.c
	gcc -c gpiod_lib.c
clean:
	rm -f *.out *.bin *.txt out.elf *.o
