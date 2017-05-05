#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <errno.h>

// Este codigo requer a biblioteca wringPi. Compile-o usando
//    gcc Ex4.c -lwiringPi -o Ex4.out
// Este codigo ainda apresenta erros
// na recepcao de dados vindos do MSP430

// Arquivo de acesso a porta serial
#define TTY "/dev/ttyAMA0"
// Arquivo de acesso a porta serial
// PARA O RASPBERRY PI 3
//#define TTY "/dev/ttyS0"

int uart0_fd;
void ctrl_c(void)
{
	puts(" Fechando " TTY "...");
	close(uart0_fd);
	exit(-1);
}

int main(void)
{
	unsigned char msp430_input=1;
	int serial_status;

	signal(SIGINT, ctrl_c);
	uart0_fd = serialOpen(TTY, 9600);
	if(uart0_fd==-1)
	{
		puts("Erro abrindo a UART. Garanta que ela nao");
		puts("esteja sendo usada por outra aplicacao.");
		return -1;
	}
	if(wiringPiSetup() == -1)
	{
		puts("Erro em wiringPiSetup().");
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
}
