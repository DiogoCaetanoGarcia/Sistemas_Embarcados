#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringSerial.h>

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
	char cellphone_input;

	signal(SIGINT, ctrl_c);
	if(wiringPiSetup() == -1)
	{
		puts("Erro em wiringPiSetup().");
		return -1;
	}
	uart0_fd = serialOpen(TTY, 115200);
	if(uart0_fd==-1)
	{
		puts("Erro abrindo a UART. Garanta que ela nao esteja sendo usada por outra aplicacao.");
		return -1;
	}
	serialFlush(uart0_fd);
	while(1)
	{
		puts("Envie um caractere pelo telefone celular:");
		cellphone_input = serialGetchar(uart0_fd);
		if(cellphone_input=='0')
		{
			puts("\tTelefone celular mandou apagar o LED.");
			system("sudo sh -c \"echo 0 > /sys/class/leds/ACT/brightness\"");
			serialPrintf(uart0_fd, "Confira o LED do RPi!\n");
		}
		else if(cellphone_input=='1')
		{
			puts("\tTelefone celular mandou acender o LED.");
			system("sudo sh -c \"echo 1 > /sys/class/leds/ACT/brightness\"");
			serialPrintf(uart0_fd, "Confira o LED do RPi!\n");
		}
		else if(cellphone_input=='2')
		{
			puts("\tTelefone celular mandou parar o programa.");
			serialPrintf(uart0_fd, "Terminando programa!\n");
			break;
		}
		else
		{
			printf("\tTelefone celular mandou caractere desconhecido: %c\n",
				cellphone_input);
			serialPrintf(uart0_fd, "Caractere %c desconhecido!\n", cellphone_input);
		}
	}
	system("sudo sh -c \"echo 0 > /sys/class/leds/ACT/brightness\"");
	serialClose(uart0_fd);
	return 0;
}

