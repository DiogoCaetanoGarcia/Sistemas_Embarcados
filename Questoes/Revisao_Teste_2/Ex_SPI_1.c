#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <signal.h>
#include <unistd.h>

#define N 100
#define PERIODO 10e3
#define DLY 100

int spi_fd;
void ctrl_c(int sig)
{
	close(spi_fd);
	exit(-1);
}

int main(void)
{
	unsigned int sum = 0;
	unsigned int counter = 0;
	unsigned char send_msp430;

	signal(SIGINT, ctrl_c);
	wiringPiSetup();
	spi_fd = wiringPiSPISetup (0, 500000);
	while(1)
	{
		usleep(PERIODO);
		do
		{
			send_msp430 = 0x55;
			wiringPiSPIDataRW(0, &send_msp430, 1);
		} while(send_msp430!=0xAA);
		usleep(DLY);
		send_msp430 = 0x1;
		wiringPiSPIDataRW(0, &send_msp430, 1);
		sum += (unsigned int) send_msp430;
		send_msp430 = 0x2;
		wiringPiSPIDataRW(0, &send_msp430, 1);
		sum += ((unsigned int) send_msp430)<<8;
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
