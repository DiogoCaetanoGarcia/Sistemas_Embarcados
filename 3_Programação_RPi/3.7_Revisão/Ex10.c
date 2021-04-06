#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int spi_fd;
void ctrl_c(int sig)
{
	close(spi_fd);
	exit(-1);
}

int main(void)
{
	char buffer;
	int contador;
	float media;

	signal(SIGINT, ctrl_c);
	wiringPiSetup();
	spi_fd = wiringPiSPISetup (0, 500000);
	contador = 0;
	media = 0.0;
	while(1)
	{
		usleep(10000);
		do
		{
			buffer = 0x55;
			wiringPiSPIDataRW(0, &buffer, 1);
		}while(buffer!=0xAA);
		buffer = 1;
		wiringPiSPIDataRW(0, &buffer, 1);
		media += (float)buffer;
		buffer = 2;
		wiringPiSPIDataRW(0, &buffer, 1);
		media += (float)(buffer<<8);
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

