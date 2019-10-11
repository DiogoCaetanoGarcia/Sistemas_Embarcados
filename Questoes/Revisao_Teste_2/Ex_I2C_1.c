#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#define N 100
#define PERIODO 10e3
#define DLY 100
#define ARQ_I2C "/dev/i2c-1"

int i2c_fd;
void ctrl_c(int sig)
{
	close(i2c_fd);
	exit(-1);
}

int main(void)
{
	unsigned int sum = 0;
	unsigned int counter = 0;
	unsigned char slave_addr=0xF, i2c_out, i2c_in[2];

	signal(SIGINT, ctrl_c);
	i2c_fd = open(ARQ_I2C, O_RDWR);
	ioctl(i2c_fd, I2C_SLAVE, slave_addr);
	while(1)
	{
		usleep(PERIODO);
		i2c_out = 0x55;
		write(i2c_fd, &i2c_out, 1);
		usleep(DLY);
		read(i2c_fd, &i2c_in, 2);
		sum += (unsigned int) i2c_in[0];
		sum += ((unsigned int) i2c_in[1])<<8;
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
