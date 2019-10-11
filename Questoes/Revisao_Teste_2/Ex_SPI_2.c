#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

int spi_fd;
void ctrl_c(int sig)
{
	puts(" Fechando SPI...");
	close(spi_fd);
	exit(-1);
}

void leitura_AD(int sig)
{
	unsigned char send_msp430;
	static unsigned int leitura=0, amostras=0;
	do
	{
		send_msp430 = 0x55;
		wiringPiSPIDataRW(0, &send_msp430, 1);
	} while(send_msp430!=0xAA);
	usleep(100);
	send_msp430 = 0x1;
	wiringPiSPIDataRW(0, &send_msp430, 1);
	leitura += (unsigned int)send_msp430;
	send_msp430 = 0x2;
	wiringPiSPIDataRW(0, &send_msp430, 1);
	leitura += ((unsigned int)send_msp430) << 8;
	amostras++;
	if(amostras==100)
	{
		leitura = (leitura+50)/100;
		system("date +%T");
		printf("Leitura A/D = %d\n", leitura);
		leitura = amostras = 0;
	}
}

int main(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGALRM, leitura_AD);
	wiringPiSetup();
	spi_fd = wiringPiSPISetup (0, 500000);
	ualarm(1, 10000);
	while(1);
	return 0;
}
