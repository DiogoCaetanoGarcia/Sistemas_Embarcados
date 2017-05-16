#include <msp430g2553.h>
#include <legacymsp430.h>

// Codigo para o MSP430 configurado como
// escravo SPI

#define LED BIT0
#define SCL BIT6
#define SDA BIT7
#define DLY 0x6000

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

void init_I2C(volatile unsigned int slave_address)
{
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL1 &= ~UCTR;
	UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Master, synchronous mode
	UCB0I2COA = slave_address; //|UCGCEN;
	P1SEL |= SCL | SDA;                       // Assign I2C pins to USCI_B0
	P1SEL2|= SCL | SDA;                       // Assign I2C pins to USCI_B0
	UCB0STAT &= ~(UCSTPIFG | UCSTTIFG);
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
	IE2 |= UCB0RXIE;// + UCB0TXIE;               //Enable RX and TX interrupt
	//UCB0I2CIE |= UCSTPIE | UCSTTIE;
}

void Transmit(unsigned char data[], unsigned int len)
{
	volatile unsigned int i;
	for(i=0; i<len; i++)
	{
		while((IFG2 & UCB0TXIFG)==0);
		UCB0TXBUF = data[i];
	}
}

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	P1DIR |= LED;
	P1OUT &= ~LED;
	init_I2C(0xF); //0xAD);
	Pisca(LED, 1, DLY);
	_BIS_SR(LPM0_bits + GIE);
	return 0;
}

interrupt(USCIAB0TX_VECTOR) USCIAB0TX_ISR(void)
{
	unsigned char d;
	if(IFG2 & UCB0RXIFG)
	{
		d = UCB0RXBUF;
		if(d<6)
			Pisca(LED, d, DLY);
		while( (UCB0STAT & UCSTTIFG)==0);
		Transmit(&d, 1);
		UCB0STAT &= ~(UCSTPIFG | UCSTTIFG);
	}
	IFG2 &= ~(UCB0TXIFG|UCB0RXIFG);
}
