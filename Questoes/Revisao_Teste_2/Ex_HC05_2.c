#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <unistd.h>

// Arquivo de acesso a porta serial
// #define TTY "/dev/ttyAMA0"
// Arquivo de acesso a porta serial
// PARA O RASPBERRY PI 3 E PARA O RPI0W
#define TTY "/dev/ttyS0"
#define BAUD_RATE 115200

int uart0_fd;
void ctrl_c(int sig)
{
	puts(" Fechando " TTY "...");
	serialClose(uart0_fd);
	exit(-1);
}

void write_HC05(int fd, char *str)
{
	int i;
	for(i=0; str[i]!='\0';i++)
	{
		serialPutchar(fd, str[i]);
	}
	serialPutchar(fd, '\r');
	serialPutchar(fd, '\n');
}

void read_HC05(int fd, char *str)
{
	int i, ok=1;
	str[0] = serialGetchar(fd);
	str[1] = ' ';
	for(i=1; ok==1; i++)
	{
		str[i] = serialGetchar(fd);
		ok = !((str[i-1]=='\r')&&(str[i]=='\n'));
	}
	str[i] = '\0';
}

int main(int argc, char *argv[])
{
	char pedido[200];
	char resposta[200];

	signal(SIGINT, ctrl_c);
	wiringPiSetup();
	uart0_fd = serialOpen(TTY, BAUD_RATE);
	serialFlush(uart0_fd);
	do
	{
		puts("Esperando pedido via Bluetooth...");
		read_HC05(uart0_fd, pedido);
		printf("Recebido: %s", pedido);
		sprintf(resposta, "RPi: %s", pedido);
		write_HC05(uart0_fd, resposta);
	}while(strcmp(pedido, "SAIR\r\n"));
	serialClose(uart0_fd);
	return 0;
}
