#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

// Para RPi 0, 1 e 2
// #define TTY "/dev/ttyAMA0"
// Para RPi 0W, 3 e 4
#define TTY "/dev/ttyS0"

int uart0_fd;
void ctrl_c(int sig)
{
	puts(" Fechando " TTY "...");
	close(uart0_fd);
	exit(-1);
}

int main(void)
{
	struct termios options;
	char user_input, msp430_return=0;

	signal(SIGINT, ctrl_c);
	uart0_fd = open(TTY, O_RDWR); // | O_NOCTTY); // | O_NDELAY);
	if(uart0_fd==-1)
	{
		puts("Erro abrindo a UART. Garanta que ela nao esteja sendo usada por outra aplicacao.");
		return -1;
	}
	puts(TTY " aberto.");
	tcgetattr(uart0_fd, &options);
	options.c_cflag = CS8 | CREAD | CLOCAL;
	options.c_iflag = 0;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN]  = 1;
	cfsetospeed(&options, B9600);
	cfsetispeed(&options, B9600);
	tcflush(uart0_fd, TCIOFLUSH);
	tcsetattr(uart0_fd, TCSANOW, &options);
	puts("UART configurada:");
	system("stty -F " TTY);
	puts("");
	user_input = 1;
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
			//tcflush(uart0_fd, TCIOFLUSH);
			if(write(uart0_fd, &user_input, 1)==1)
			{
				sleep(1+user_input/2);
				//if(read(uart0_fd, &msp430_return, 1)==1)
				//	printf("MSP430_return = %d\n", msp430_return);
			}
			else
			{
				puts("Nao conseguiu mandar os dados.");
			}
		}
		puts("");
	}
	close(uart0_fd);
	return 0;
}
