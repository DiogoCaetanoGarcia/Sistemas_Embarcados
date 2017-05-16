#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include <linux/i2c-dev.h>
//#include <wiringPi.h>
//#include <wiringSerial.h>
//#include <errno.h>

// Este codigo requer a biblioteca wringPi. Compile-o usando
//    gcc Ex2.c -lwiringPi -o Ex2.out

int i2c_fd;
void ctrl_c(int sig)
{
	close(i2c_fd);
	exit(-1);
}

int main(void)
{
	unsigned char user_input=1, msp430_ret, rpi_addr = 0xDA, slave_addr=0x0F;
	signal(SIGINT, ctrl_c);
	i2c_fd = open("/dev/i2c-1", O_RDWR);
	ioctl(i2c_fd, I2C_SLAVE, slave_addr);
/*	
	if(wiringPiSetup() == -1)
	{
		puts("Erro em wiringPiSetup().");
		return -1;
	}
	spi_fd = wiringPiSPISetup (0, 500000);
	if(spi_fd==-1)
	{
		puts("Erro abrindo a SPI. Garanta que ela nao");
		puts("esteja sendo usada por outra aplicacao.");
		return -1;
	}*/
	while(user_input!=0)
	{
		puts("Digite um numero entre 1 e 5");
		puts("para mandar o MSP430 piscar seus LEDs,");
		puts("ou digite 0 para terminar o programa. ");
		scanf("%d", &user_input);
		if((user_input<0) || (user_input>5))
			puts("Valor invalido");
		else if(user_input>0)
		{
			write(i2c_fd, &user_input, 1);
			sleep(1+user_input/2);
			read(i2c_fd, &msp430_ret, 1);
			printf("MSP430_return = %d\n", msp430_ret);
		}
		puts("");
	}
	close(i2c_fd);
}
