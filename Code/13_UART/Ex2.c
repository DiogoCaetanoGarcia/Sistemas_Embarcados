#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>

// Este codigo requer a biblioteca wringPi:
// http://wiringpi.com/download-and-install/
// Compile-o usando
//    gcc Ex2.c -lwiringPi -o Ex2.out

// Arquivo de acesso a porta serial
#define TTY "/dev/ttyAMA0"
// Arquivo de acesso a porta serial
// PARA O RASPBERRY PI 3
//#define TTY "/dev/ttyS0"

int uart0_fd;
void ctrl_c(int sig)
{
	puts(" Fechando " TTY "...");
	serialClose(uart0_fd);
	exit(-1);
}

int main(void)
{
	unsigned char user_input=1;

	signal(SIGINT, ctrl_c);
	uart0_fd = serialOpen(TTY, 9600);
	if(uart0_fd==-1)
	{
		puts("Erro abrindo a UART. Garanta que ela nao esteja sendo usada por outra aplicacao.");
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
	while(user_input!=0)
	{
		puts("Digite um numero entre 1 e 5");
		puts("para mandar o MSP430 piscar seus LEDs,");
		puts("ou digite 0 para terminar o programa. ");
		scanf("%d", &user_input);
		if((user_input<0) || (user_input>5))
			puts("Valor invalido");
		else if(user_input>0)
		{
			serialPutchar(uart0_fd, user_input);
			sleep(1+user_input/2);
		}
		puts("");
	}
	serialClose(uart0_fd);
}
