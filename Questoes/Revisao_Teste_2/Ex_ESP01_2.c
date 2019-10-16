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
#define BAUD_RATE 9600

int uart0_fd;
void ctrl_c(int sig)
{
	puts(" Fechando " TTY "...");
	serialClose(uart0_fd);
	exit(-1);
}

void write_ESP01(int fd, char *str)
{
	int i;
	for(i=0; str[i]!='\0';i++)
	{
		serialPutchar(fd, str[i]);
	}
	serialPutchar(fd, '\r');
	serialPutchar(fd, '\n');
}

void read_ESP01(int fd, char *str)
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
	char resposta_final[200];
	char resposta[200];

	if(argc<3)
	{
		printf("Teste de comunicação com o ESP-01, por envio\n");
		printf("de pedidos AT. Por exemplo, tente:\n");
		printf("   %s AT OK\n", argv[0]);
		printf("   %s AT+CWLAP OK\n", argv[0]);
		printf("   %s AT+GMR OK\n", argv[0]);
		printf("   %s AT+CIFSR OK\n", argv[0]);
		return -2;
	}
	sprintf(resposta_final,"%s\r\n",argv[2]);
	signal(SIGINT, ctrl_c);
	wiringPiSetup();
	uart0_fd = serialOpen(TTY, BAUD_RATE);
	serialFlush(uart0_fd);
	printf("Fazendo pedido %s...\n", argv[1]);
	write_ESP01(uart0_fd, argv[1]);
	do
	{
		read_ESP01(uart0_fd, resposta);
		printf("%s", resposta);
	} while(strcmp(resposta, resposta_final));
	serialClose(uart0_fd);
	return 0;
}
