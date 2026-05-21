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
	int leituras[2], contador;
	float media;

	signal(SIGINT, ctrl_c);
	wiringPiSetup();
	uart0_fd = serialOpen(TTY, 9600);
	serialFlush(uart0_fd);
	contador = 0;
	media = 0.0;
	while(1)
	{
		leituras[0] = (int) serialGetchar(uart0_fd);
		leituras[1] = (int) serialGetchar(uart0_fd);
		media += (float)(leituras[0] + (leituras[1]<<8));
		contador++;
		if(contador==100)
		{
			media /= 100.0;
			printf("Media(A/D) = %f\n", media);
			media = 0.0;
			contador = 0;
		}
	}
	return 0;
}
