#include <msp430g2553.h>
#include <legacymsp430.h>

#define RX BIT1
#define TX BIT2
#define BTN BIT3
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
	P1SEL2 = P1SEL = RX+TX;
	P1DIR |= LEDS;
	P1OUT &= ~LEDS;
	P1DIR &= ~BTN;
	P1REN |= BTN;
	P1OUT |= BTN;
	P1IES = 0;
	P1IE  = BTN;
	UCA0CTL0 = 0;
	UCA0CTL1 = UCSSEL_2;
	UCA0BR0 = 6;
	UCA0BR1 = 0;
	UCA0MCTL = UCBRF_8 + UCOS16;
	IE2 |= UCA0RXIE;
	Pisca(LEDS, 1, DLY1);
	_BIS_SR(LPM0_bits + GIE);
	return 0;
}

interrupt(PORT1_VECTOR) P1_ISR(void)
{
	static unsigned char count = 0;
	Pisca(LED1, count, DLY1);
	Send_Data(count);
	//count = (count+1)%6;
	count = (count==5)?0:(count+1);
	P1IFG &= ~BTN;
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
