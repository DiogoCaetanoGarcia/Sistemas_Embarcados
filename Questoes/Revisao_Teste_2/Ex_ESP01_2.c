#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <signal.h>

// Arquivo de acesso a porta serial
//#define TTY "/dev/ttyAMA0"
// Arquivo de acesso a porta serial
// PARA O RASPBERRY PI 3 E O RPI Zero
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
	unsigned int sum = 0;
	unsigned int counter = 0;

	signal(SIGINT, ctrl_c);
	wiringPiSetup();
	uart0_fd = serialOpen(TTY, 9600);
	serialFlush(uart0_fd);
	
	while(1)
	{
		sum += (unsigned int) serialGetchar(uart0_fd);
		sum += ((unsigned int) serialGetchar(uart0_fd))<<8;
		counter++;
		if(counter==N)
		{
			sum += (N/2);
			sum /= N;
			system("date +%T");
			printf("Media das amostras = %d\n", sum);
			sum = 0;
			counter = 0;
		}
	}
}

