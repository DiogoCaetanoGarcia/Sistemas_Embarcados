all: Ex01.out Ex02.out Ex03.out Ex04.out Ex05.out Ex06.out Ex07.out Ex08.out Ex09.out Ex10.out Ex11.out
Ex01.out: Ex01.c
	gcc Ex01.c -o Ex01.out -lwiringPi
Ex02.out: Ex02.c
	gcc Ex02.c -o Ex02.out -lwiringPi
Ex03.out: Ex03.c
	gcc Ex03.c -o Ex03.out -lwiringPi
Ex04.out: Ex04.c
	gcc Ex04.c -o Ex04.out -lwiringPi
Ex05.out: Ex05.c
	gcc Ex05.c -o Ex05.out -lwiringPi
Ex06.out: Ex06.c
	gcc Ex06.c -o Ex06.out -lwiringPi
Ex07.out: Ex07.c
	gcc Ex07.c -o Ex07.out -lwiringPi
Ex08.out: Ex08.c
	gcc Ex08.c -o Ex08.out -lpthread -lwiringPi
Ex09.out: Ex09.c
	gcc Ex09.c -o Ex09.out -lpthread -lwiringPi
Ex10.out: Ex10.c
	gcc Ex10.c -o Ex10.out -lwiringPi
Ex11.out: Ex11.c
	gcc Ex11.c -o Ex11.out -lwiringPi
MSP_UART:
	# Para compilar códigos para o MSP430 em Linux, execute
	# sudo apt-get install msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
	msp430-gcc -Os -Wall -g -mmcu=msp430g2553 -o out.elf MSP430_AD_UART.c
	sudo mspdebug rf2500 "prog out.elf"
	rm out.elf
MSP_SPI:
	# Para compilar códigos para o MSP430 em Linux, execute
	# sudo apt-get install msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
	msp430-gcc -Os -Wall -g -mmcu=msp430g2553 -o out.elf MSP430_AD_SPI.c
	sudo mspdebug rf2500 "prog out.elf"
	rm out.elf
MSP_I2C:
	# Para compilar códigos para o MSP430 em Linux, execute
	# sudo apt-get install msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
	msp430-gcc -Os -Wall -g -mmcu=msp430g2553 -o out.elf MSP430_AD_I2C.c
	sudo mspdebug rf2500 "prog out.elf"
	rm out.elf
clean:
	rm -f *.out *.bin *.txt out.elf
