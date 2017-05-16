/* 

Codigo para o MSP430 funcionar como mestre SPI que
pede dados a outro MSP430 (escravo SPI) de acordo
com o seguinte protocolo, apos o usuario pressionar
o botao do pino P1.3:

	I. Enviar o byte 0x55 e receber o byte 0xAA,
		o que indica o começo de uma conversão AD.
	II. Enviar os bytes 0x01 e 0x02, e receber o
		byte menos significativo e o mais
		significativo da conversão de 10 bits,
		nesta ordem.

Se o resultado da conversao AD for maior do que 1020
(ou seja, se o pino de leitura AD estiver proximo a Vcc),
o LED verde ficara aceso por 0,5 s.

Se o mestre enviar o byte inicial 0x55 e receber
outro byte que nao 0xAA, o LED vermelho ficara
aceso por 0,5 s.

Conexoes:
   P1.0: LED vermelho da placa Launchpad
   P1.1: conexao SPI MISO
   P1.2: conexao SPI MOSI
   P1.3: botao da placa Launchpad
   P1.4: conexao clock SPI
   P1.6: LED verde da placa Launchpad

*/

#include <msp430g2553.h>
#include <legacymsp430.h>

#define MISO BIT1
#define MOSI BIT2
#define SCLK BIT4
#define BTN BIT3
#define LED1 BIT0
#define LED2 BIT6
#define LEDs (BIT0|BIT6)
#define WAIT_SPI while( (IFG2 & UCA0RXIFG) == 0)

void Send_Data(volatile unsigned char c)
{
	while((IFG2&UCA0TXIFG)==0);
	UCA0TXBUF = c;
}

// Atraso de t*100 us
void Atraso(volatile unsigned int t)
{

	TACCR0 = 100-1;
	TACTL |= TACLR;
	TACTL = TASSEL_2 + ID_0 + MC_1;
	while(t--)
	{
		while((TACTL&TAIFG)==0);
		TACTL &= ~TAIFG;
	}
	TACTL = MC_0;
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	P1SEL2 = P1SEL = MOSI+MISO+SCLK;
	
	P1OUT |= BTN;
	P1REN |= BTN;
	P1DIR &= ~BTN;
	P1IE = P1IES = BTN;
	P1OUT &= ~LEDs;
	P1DIR |= LEDs;

	UCA0CTL1 = UCSWRST;
	UCA0CTL1 |= UCSSEL_3;
	UCA0MCTL = 0;
	UCA0BR0 = 1;
	UCA0BR1 = 0;
	UCA0CTL0 = UCCKPH + UCMST + UCMSB + UCMODE_0 + UCSYNC;
	UCA0CTL1 &= ~UCSWRST;
	
	_BIS_SR(LPM4_bits + GIE);
	return 0;
}

interrupt(PORT1_VECTOR) P1_ISR(void)
{
	volatile unsigned int d=0;
	P1OUT &= ~LEDs;
	while((P1IN&BTN)==0);
	Send_Data(0x55);
	WAIT_SPI;
	if(UCA0RXBUF== 0xAA)
	{
		Atraso(1);
		Send_Data(0x01);
		WAIT_SPI;
		d = UCA0RXBUF;

		Send_Data(0x02);
		WAIT_SPI;
		d |= (UCA0RXBUF<<8);
		
		if(d>1020)
			P1OUT |= LED2;
	}
	else
		P1OUT |= LED1;

	Atraso(5000);
	P1OUT &= ~LEDs;
	P1IFG &= ~BTN;
}
