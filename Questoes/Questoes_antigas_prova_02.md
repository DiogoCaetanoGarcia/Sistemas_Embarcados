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

5. Controle 6 LEDs de uma árvore de natal utilizando charlieplexing, de forma que um ser humano veja todos acesos ao mesmo tempo. Pisque os LEDs numa frequência de 100 Hz.

6. Controle 6 LEDs de uma árvore de natal utilizando charlieplexing. Pisque os LEDs numa frequência de 100 Hz. Acenda os LEDs de forma que um ser humano veja dois LEDs acesos juntos por um tempo, depois outros dois LEDs, e depois os últimos 2 LEDs juntos. Permaneça em cada estado durante 0,5 segundos.

7. Multiplexe 2 displays de 7 segmentos para apresentar a seguinte sequência em loop:

```
01 - 12 - 23 - 34 - 45 - 56 - 67 - 78 - 89 - 9A - AB - BC - CD - DE - EF - F0
```

Pisque os LEDs numa frequência de 100 Hz.

8. Implemente a comunicação UART em um pino GPIO, usando um bit de START (padrão), oito bits de dados na ordem MSB->LSB e um bit de STOP.

(a) Escreva a seguinte função em C para configurar pinos GPIO para transmissão e recepção: `void Config_UART(unsigned char TX_pin, unsigned char RX_pin);`, onde `TX_pin` e `RX_pin` são os valores dos pinos GPIO na Raspberry Pi.

(b) Escreva a seguinte função em C para imitar a transmissão UART em um pino GPIO da Raspberry Pi: `void Transmit_UART(unsigned char data_out, unsigned char TX_pin, unsigned char baud_rate);`, onde `data_out` é o byte a ser enviado, `TX_pin` é o valor do pino GPIO de transmissão, e `baud_rate` é a taxa de transmissão UART, em amostras por segundo.

(c) Escreva a seguinte função em C para imitar a recepção UART em um pino GPIO da Raspberry Pi: `unsigned char Receive_UART(unsigned char RX_pin, unsigned char baud_rate);`, onde `RX_pin` é o valor do pino GPIO de recepção, e `baud_rate` é a taxa de recepção UART, em amostras por segundo. A função retorna o byte lido.

(d) Escreva a seguinte função em C para liberar os pinos GPIO de transmissão e recepção: `void Release_UART(unsigned char TX_pin, unsigned char RX_pin);`

9. Considere dois MSP430, onde um deles faz leituras AD em 8 canais, e o outro escreve em 4 displays de 7 segmentos. Ambos estão conectados ao Raspberry Pi pelas portas I2C, e seus respectivos endereços são `0x20` e `0x51`, respectivamente.

(a) Escreva a função em C `void Config_I2C(void);` para configurar a comunicação I2C no Raspberry Pi.

(b) Escreva a função em C `unsigned int AD_read_I2C(char channel);` para ler uma conversão AD de 10 bits do MSP430 de um dos oito canais. O Raspberry Pi manda o número do canal para o MSP430, aguarda 100us, e lê os bytes menos e mais significativos da conversão, nessa ordem.

(c) Escreva a função em C `void Write_4_7seg_I2C(unsigned int value);` para escrever nos displays a leitura atual de tensão. Considere que o MSP430 mede tensões entre 0 e 3 V, e que o conversor AD é de 10 bits. O MSP430 deverá receber a casas decimais do valor, da casa mais significativa para a menos significativa. Por exemplo, se `value=1023`, a Raspberry Pi deverá transmitir o vetor `{3,0,0,0}`.

10. Considere dois MSP430, onde um deles faz leituras AD em 8 canais, e o outro escreve em 4 displays de 7 segmentos. Ambos estão conectados ao Raspberry Pi pelas portas SPI.

(a) Escreva a função em C `void Config_SPI(void);` para configurar a comunicação SPI no Raspberry Pi.

(b) Escreva a função em C `unsigned int AD_read_SPI(char channel);` para ler uma conversão AD de 10 bits do MSP430 de um dos oito canais. O Raspberry Pi manda o número do canal para o MSP430, aguarda 100us, e lê os bytes menos e mais significativos da conversão, nessa ordem.

(c) Escreva a função em C `void Write_4_7seg_SPI(unsigned int value);` para escrever nos displays a leitura atual de tensão. Considere que o MSP430 mede tensões entre 0 e 3 V, e que o conversor AD é de 10 bits. O MSP430 deverá receber a casas decimais do valor, da casa mais significativa para a menos significativa. Por exemplo, se `value=1023`, a Raspberry Pi deverá transmitir o vetor `{3,0,0,0}`.
