#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

int i2c_fd;
void ctrl_c(int sig)
{
	close(i2c_fd);
	exit(-1);
}

int main(void)
{
	unsigned char user_input=1, microcontroller_ret, slave_addr=0x0F;
	signal(SIGINT, ctrl_c);
	i2c_fd = open("/dev/i2c-1", O_RDWR);
	ioctl(i2c_fd, I2C_SLAVE, slave_addr);

	while(user_input!=0)
	{
		puts("Digite um numero entre 1 e 5 para mandar");
		puts("o microcontrolador piscar seus LEDs,");
		puts("ou digite 0 para terminar o programa. ");
		scanf("%d", &user_input);
		if((user_input<0) || (user_input>5))
			puts("Valor invalido");
		else if(user_input>0)
		{
			write(i2c_fd, &user_input, 1);
			sleep(1+user_input/2);
			read(i2c_fd, &microcontroller_ret, 1);
			printf("Retorno do microcontrolador = %d\n", microcontroller_ret);
		}
		puts("");
	}
	close(i2c_fd);
	return 0;
}
