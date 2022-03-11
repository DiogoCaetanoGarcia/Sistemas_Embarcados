all: Ex1.out Ex2.out Ex4.out
Ex1.out: Ex1.c
	gcc Ex1.c -o Ex1.out
Ex2.out: Ex2_HC05_UART.c
	gcc Ex2_HC05_UART.c    -o Ex2.out -lwiringPi
Ex4.out: Ex4_HMC5883L_I2C.c
	gcc Ex4_HMC5883L_I2C.c -o Ex4.out -lm
MSPcode:
	# Para compilar códigos para o MSP430 em Linux, execute
	# sudo apt-get install msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
	msp430-gcc -Os -Wall -g -mmcu=msp430g2553 -o out.elf MSP430_code.c
	sudo mspdebug rf2500 "prog out.elf"
	rm out.elf
clean:
	rm -f *.out *.o *.bin *.txt *.html
