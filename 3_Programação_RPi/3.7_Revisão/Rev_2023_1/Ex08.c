#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

float media;
int contador;
int i2c_fd;

void ctrl_c(int sig)
{
	close(i2c_fd);
	exit(-1);
}

void conversor_AD(int sig)
{
	char buffer_I2C[2];
	buffer_I2C[0] = 0x55;
	write(i2c_fd, &buffer_I2C[0], 1);
	usleep(100);
	read(i2c_fd, buffer_I2C, 2);
	media += (float)buffer_I2C[0];
	media += ((float)buffer_I2C[1])*256.0;
	contador++;
	if(contador==100)
	{
		media /= 100.0;
		printf("Media(A/D) = %f\n", media);
		media = 0.0;
		contador = 0;
	}
}

int main(void)
{
	unsigned char slave_addr=0x0F;
	i2c_fd = open("/dev/i2c-1", O_RDWR);
	ioctl(i2c_fd, I2C_SLAVE, slave_addr);
	media = 0.0;
	contador = 0;
	signal(SIGINT,  ctrl_c);
	signal(SIGALRM, conversor_AD);
	ualarm(10000, 10000);
	while(1);
	return 0;
}
