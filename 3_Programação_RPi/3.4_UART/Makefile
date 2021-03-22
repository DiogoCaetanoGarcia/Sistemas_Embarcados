all: Ex1.out Ex2.out Ex3.out Ex4.out
Ex1.out: Ex1.c
	gcc Ex1.c -o Ex1.out
Ex2.out: Ex2.c
	gcc Ex2.c -o Ex2.out -lwiringPi
Ex3.out: Ex3.c
	gcc Ex3.c -o Ex3.out -lwiringPi
Ex4.out: Ex4.c
	gcc Ex4.c -o Ex4.out -lwiringPi
MSPcode:
	# Para compilar códigos para o MSP430 em Linux, execute
	# sudo apt-get install msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
	msp430-gcc -Os -Wall -g -mmcu=msp430g2553 -o out.elf MSP430_code.c
	sudo mspdebug rf2500 "prog out.elf"
	rm out.elf
clean:
	rm -f *.out *.o *.bin *.txt *.html out.elf
