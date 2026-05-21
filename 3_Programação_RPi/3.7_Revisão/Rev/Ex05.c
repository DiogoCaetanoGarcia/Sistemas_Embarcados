#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>

int spi_fd;
void ctrl_c(int sig)
{
	close(spi_fd);
	exit(-1);
}

int main(void)
{
	char buffer_SPI;
	float media;
	int contador;

	signal(SIGINT, ctrl_c);
	wiringPiSetup();
	spi_fd = wiringPiSPISetup (0, 500000);
	media = 0.0;
	contador = 0;
	while(1)
	{
		usleep(10000);
		buffer_SPI = 0x55;
		wiringPiSPIDataRW(0, &buffer_SPI, 1);
		if(buffer_SPI != 0xAA)
		{
			buffer_SPI = 0x02;
			wiringPiSPIDataRW(0, &buffer_SPI, 1);
			buffer_SPI = 0x55;
			wiringPiSPIDataRW(0, &buffer_SPI, 1);
		}
		usleep(100);
		buffer_SPI = 0x01;
		wiringPiSPIDataRW(0, &buffer_SPI, 1);
		media += (float)buffer_SPI;
		buffer_SPI = 0x02;
		wiringPiSPIDataRW(0, &buffer_SPI, 1);
		media += ((float)buffer_SPI)*256.0;
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
