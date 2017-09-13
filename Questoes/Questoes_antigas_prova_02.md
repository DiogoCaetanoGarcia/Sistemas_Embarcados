1. Crie duas threads, e faça com que uma gere uma onda quadrada em um pino GPIO, enquanto a outra faz polling de um botão em outro pino GPIO, aumentando a frequência da onda sempre que o botão for pressionado. A frequência da onda quadrada deve começar em 1 Hz, e dobrar cada vez que o botão for pressionado. A frequência máxima é de 64 Hz, devendo retornar a 1 Hz se o botão for pressionado novamente.

2. Considere um MSP430 que faz leituras A/D em 8 canais, conectado ao Raspberry Pi pelas portas I2C. O endereço I2C do MSP430 é `0x20`. Para ler uma conversão A/D de 10 bits do MSP430 em um dos oito canais, o Raspberry Pi manda o número do canal para o MSP430, aguarda 100us, e lê os bytes menos e mais significativos da conversão, nessa ordem.

Programe o Raspberry Pi para ler os 8 canais A/D sequencialmente a cada 0,5 segundo, e mostrar no terminal os valores máximo, mínimo e médio das leituras dos 8 canais.

3. Considerando o código abaixo, responda:

```C
#include <stdio.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <unistd.h>

#define N 100

void poll_btn(struct pollfd *pfd)
{
	char buffer, vals[N]={0};
	int  pos=0, test=1, i, s;
	lseek(pfd->fd, 0, SEEK_SET);
	read(pfd->fd, &buffer, 1);
	poll(pfd, 1, -1);
	while(test)
	{
		lseek(pfd->fd, 0, SEEK_SET);
		read(pfd->fd, vals+pos, 1);
		vals[pos] -= '0';
		pos=(pos+1)%N;
		for(s=i=0;i<N;i++) s+=vals[i];
		if(buffer=='0')
			test = s<(N/2);
		else
			test = s>(N/2);
	}
}

int main(void)
{

	struct pollfd pfd;
	int btn_press;
	system("echo 4	  > /sys/class/gpio/export");
	system("echo both > /sys/class/gpio/gpio4/edge");
	system("echo in   > /sys/class/gpio/gpio4/direction");
	pfd.fd = open("/sys/class/gpio/gpio4/value", O_RDONLY);
	pfd.events = POLLPRI | POLLERR;
	for(btn_press=0; btn_press<5; btn_press++)
	{
		puts("Pressione o botao...");
		poll_btn(&pfd);
		puts("Borda de descida!");
		poll_btn(&pfd);
		puts("Borda de subida!");
	}
	close(pfd.fd);
	system("echo 4 > /sys/class/gpio/unexport");
	return 0;
}
```

(a) Como o código acima executa o debounce do botão? Justifique sua resposta.
(b) Em quais bordas (subida/descida) é feito o debounce? Justifique sua resposta.
(c) Qual é a utilidade da variável 'test' dentro da função 'poll_btn()'? Justifique sua resposta.
(d) Por que a função 'lseek()' é sempre chamada antes da função 'read()' dentro da função 'poll_btn()'? Justifique sua resposta.

4. Com o código abaixo, o Raspberry Pi obtém dados de conversão A/D de 10 bits de um MSP430, seguindo um padrão previamente estabelecido para os dois. O Raspberry Pi periodicamente apresenta a média móvel das leituras no terminal. Com relação a este código, esponda:

```C
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>

#define N 1000
#define M 50

int sample = 0, d[N], ms = 0;
int fd;
double m=0.0;

void loop(int sig)
{
	unsigned char txrx;

	ualarm(500);
	do
	{
		txrx = 0xA5;
		wiringPiSPIDataRW(0, &txrx, 1);
	} while(txrx != 0x5A);
	usleep(100);
	txrx = 1;
	wiringPiSPIDataRW(0, &txrx, 1);
	d[sample] = (unsigned int)txrx;
	txrx = 2;
	wiringPiSPIDataRW(0, &txrx, 1);
	d[sample] += ((unsigned int)txrx)<<8;
	m += (double) d[sample];
	sample = (sample+1)%N;
	if(sample==0)
	{
		printf("Valor medio = %f V\n",m*3.0/1023.0/N);
		m = 0.0;
		ms++;
	}
	if(ms==M)
	{
		close(fd);
		exit(0);
	}
}

int main(void)
{
	wiringPiSetup();
	fd = wiringPiSPISetup (0, 500000);
	signal(SIGALRM, loop);
	ualarm(500);
	while(1);
}
```

(a) Qual é a sequência de bytes pré-estabelecida para o Raspberry Pi receber uma leitura A/D? Como o MSP430 responde?

(b) Qual é a taxa de amostragem das leituras A/D? Justifique.

(c) Qual é a baud rate na comunicação SPI deste código? Quem é o mestre e quem é o escravo?

(d) Quantas médias das amostras serão apresentadas no terminal? Justifique.
