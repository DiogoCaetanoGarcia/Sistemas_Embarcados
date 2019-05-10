#include <wiringPi.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define N 100

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
	unsigned long sum = 0;
	unsigned int counter = 0;

	signal(SIGINT, ctrl_c);
	uart0_fd = serialOpen(TTY, 9600);
	wiringPiSetup();
	serialFlush(uart0_fd);
	while(1)
	{
		sum += (unsigned long) serialGetchar(uart0_fd);
		sum += ((unsigned long) serialGetchar(uart0_fd))<<8;
		counter++;
		if(counter==N)
		{
			sum += (N/2);
			sum /= N;
			printf("Media das amostras = %d\n", sum);
			sum = 0;
			counter = 0;
		}
	}
}