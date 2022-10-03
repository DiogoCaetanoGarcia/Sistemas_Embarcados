MSPcode:
	# Para compilar códigos para o MSP430 em Linux, execute
	# sudo apt-get install msp430-libc mspdebug msp430mcu binutils-msp430 gcc-msp430 gdb-msp430
	msp430-gcc -Os -Wall -g -mmcu=msp430g2553 -o out.elf MSP430_code.c
	sudo mspdebug rf2500 "prog out.elf"
	rm out.elf
clean:
	rm -f *.out *.o *.bin *.txt *.html out.elf
