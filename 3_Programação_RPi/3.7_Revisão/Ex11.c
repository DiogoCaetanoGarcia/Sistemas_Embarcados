#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int i2c_fd;
void ctrl_c(int sig)
{
	close(i2c_fd);
	exit(-1);
}

int main(void)
{
	char buffer, leituras[2];
	unsigned char slave_addr = 0xF;
	int contador;
	float media;

	signal(SIGINT, ctrl_c);
	i2c_fd = open("/dev/i2c-1", O_RDWR);
	ioctl(i2c_fd, I2C_SLAVE, slave_addr);
	contador = 0;
	media = 0.0;
	while(1)
	{
		usleep(10000);
		buffer = 0x55;
		write(i2c_fd, &buffer, 1);
		usleep(100);
		read(i2c_fd, leituras, 2);
		media += (float)leituras[0];
		media += ((float)(leituras[1]))*256;
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

