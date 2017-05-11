#include <msp430g2553.h>
#include <legacymsp430.h>

// Codigo para o MSP430 configurado como
// escravo SPI

#define MISO BIT1
#define MOSI BIT2
#define SCLK BIT4
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)
#define DLY1 0x6000
#define DLY2 0x3000

void Atraso(volatile unsigned int x)
{
	while(x--);
}

void Send_Data(volatile unsigned char c)
{
	while((IFG2&UCA0TXIFG)==0);
	UCA0TXBUF = c;
}

void Pisca(unsigned char pino, char piscadas, unsigned int tempo)
{
	piscadas <<= 1;
	while(piscadas--)
	{
		P1OUT ^= pino;
		Atraso(tempo);
	}
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	P1SEL2 = P1SEL = MOSI+MISO+SCLK;
	P1DIR |= LEDS;
	P1OUT &= ~LEDS;
	UCA0CTL1 = UCSWRST + UCSSEL_3;
	UCA0CTL0 = UCCKPH+UCMSB+UCMODE_0+UCSYNC;
	UCA0CTL1 &= ~UCSWRST;
	Send_Data(10);
	IE2 |= UCA0RXIE;
	Pisca(LEDS, 1, DLY1);
	_BIS_SR(LPM0_bits + GIE);
	return 0;
}

interrupt(USCIAB0RX_VECTOR) Receive_Data(void)
{
	volatile unsigned char blink = UCA0RXBUF;
	P1OUT ^= LED1;
	if(blink<6)
	{
		Pisca(LED2, blink, DLY1);
		Send_Data(blink);
	}
	IFG2 &= ~UCA0RXIFG;
	P1OUT ^= LED1;
}
