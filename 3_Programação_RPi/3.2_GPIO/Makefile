all: Ex2.out Ex3.out Ex4.out Ex5.out Ex6.out Ex7.out Ex8.out Ex9.out Ex10.out
Ex2.out: Ex2.o gpio_sysfs.o
	gcc Ex2.o gpio_sysfs.o -o Ex2.out
Ex3.out: Ex3.o gpio_dev_mem.o
	gcc Ex3.o gpio_dev_mem.o -o Ex3.out
Ex4.out: Ex4.o gpio_dev_mem.o
	gcc Ex4.o gpio_dev_mem.o -o Ex4.out
Ex5.out: Ex5.o gpio_dev_mem.o
	gcc Ex5.o gpio_dev_mem.o -o Ex5.out
Ex6.out: Ex6.o gpio_dev_mem.o
	gcc Ex6.o gpio_dev_mem.o -o Ex6.out
Ex7.out: Ex7.c
	gcc Ex7.c -o Ex7.out -lwiringPi
Ex8.out: Ex8.c
	gcc Ex8.c -o Ex8.out -lwiringPi
Ex9.out: Ex9.c
	gcc Ex9.c -o Ex9.out -lwiringPi
Ex10.out: Ex10.c
	gcc Ex10.c -o Ex10.out -lwiringPi
Ex2.o: Ex2.c
	gcc -c Ex2.c
Ex3.o: Ex3.c
	gcc -c Ex3.c
Ex4.o: Ex4.c
	gcc -c Ex4.c
Ex5.o: Ex6.o
	gcc -c Ex5.c
Ex6.o: Ex6.c
	gcc -c Ex6.c
gpio_sysfs.o: gpio_sysfs.c
	gcc -c gpio_sysfs.c
gpio_dev_mem.o: gpio_dev_mem.c
	gcc -c gpio_dev_mem.c
clean:
	rm -f *.out *.o *.bin *.txt *.html
