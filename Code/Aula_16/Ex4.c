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

int uart0_fd;
void ctrl_c(void)
{
	puts(" Fechando /dev/ttyAMA0...");
	serialClose(uart0_fd);
	exit(-1);
}

int main(void)
{
	unsigned char msp430_input=1;
	int serial_status;

	signal(SIGINT, ctrl_c);
	uart0_fd = serialOpen("/dev/ttyAMA0", 9600);
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
	puts("/dev/ttyAMA0 aberto.");
	puts("UART configurada:");
	system("stty -F /dev/ttyAMA0");
	puts("");
	serialFlush(uart0_fd);
	while(msp430_input!=6)
	{
		msp430_input = (unsigned char) serialGetchar(uart0_fd);
		serial_status = serialDataAvail(uart0_fd);
		printf("MSP430_return = %d\n", msp430_input);
		if(serial_status==-1)
			printf("Erro = %s\n", strerror(errno));
		else
			printf("%d bytes disponiveis\n");
	}
	serialClose(uart0_fd);
}
