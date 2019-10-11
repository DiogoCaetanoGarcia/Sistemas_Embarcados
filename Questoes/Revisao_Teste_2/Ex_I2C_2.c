#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int i2c_fd;
void ctrl_c(int sig)
{
	puts(" Fechando I2C...");
	close(i2c_fd);
	exit(-1);
}

void leitura_AD(int sig)
{
	unsigned char send_msp430, i2c_rec[2];
	static unsigned int leitura=0, amostras=0;
	send_msp430 = 0x55;
	write(i2c_fd, &send_msp430, 1);
	usleep(100);
	read(i2c_fd, i2c_rec, 2);
	leitura += (unsigned int)i2c_rec[0];
	leitura += ((unsigned int)i2c_rec[1]) << 8;
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
	i2c_fd = open("/dev/i2c-1", O_RDWR);
	ioctl(i2c_fd, I2C_SLAVE, 0xF);
	ualarm(1, 10000);
	while(1);
	return 0;
}
