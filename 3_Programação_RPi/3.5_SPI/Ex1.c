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
	unsigned char user_input=1, send_microcontroller;

	signal(SIGINT, ctrl_c);
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
	}
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
			send_microcontroller = user_input;
			wiringPiSPIDataRW(0, &send_microcontroller, 1);
			printf("Retorno do microcontrolador = %d\n", send_microcontroller);
			sleep(1+user_input/2);
		}
		puts("");
	}
	close(spi_fd);
	return 0;
}
