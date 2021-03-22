#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>
#include <string.h>

// Para RPi 0, 1 e 2
// #define TTY "/dev/ttyAMA0"
// Para RPi 0W, 3 e 4
#define TTY "/dev/ttyS0"

int uart0_fd;
void ctrl_c(int sig)
{
	puts(" Fechando " TTY "...");
	serialClose(uart0_fd);
	exit(-1);
}

int main(void)
{
	unsigned char msp430_input=1;
	int serial_status;

	signal(SIGINT, ctrl_c);
	if(wiringPiSetup() == -1)
	{
		puts("Erro em wiringPiSetup().");
		return -1;
	}
	uart0_fd = serialOpen(TTY, 9600);
	if(uart0_fd==-1)
	{
		puts("Erro abrindo a UART. Garanta que ela nao");
		puts("esteja sendo usada por outra aplicacao.");
		return -1;
	}
	puts(TTY " aberto.");
	puts("UART configurada:");
	system("stty -F " TTY);
	puts("");
	serialFlush(uart0_fd);
	while(msp430_input!=5)
	{
		msp430_input = (unsigned char) serialGetchar(uart0_fd);
		serial_status = serialDataAvail(uart0_fd);
		printf("MSP430_return = %d\n", msp430_input);
		if(serial_status==-1)
			printf("Erro = %s\n", strerror(errno));
		else
			printf("%d bytes disponiveis\n", serial_status);
	}
	serialClose(uart0_fd);
	return 0;
}
