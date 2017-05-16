/* 

Codigo para o MSP430 funcionar como escravo I2C de
acordo com o seguinte protocolo:

  	I. Receber o byte 0x55, o que indica o começo
  		de uma conversão AD.
	II. Enviar o byte menos significativo e o mais
		significativo da conversão de 10 bits do
		sinal analogico no pino P1.0, nesta ordem.

Conexoes:
   P1.0: LED vermelho da placa Launchpad
   P1.3: botao da placa Launchpad
   P1.6: conexao clock I2C (SCL)
   P1.7: conexao dados I2C (SDA)

*/

#include <msp430g2553.h>
#include <legacymsp430.h>

#define AD_IN BIT0
#define AD_INCH INCH_0
#define SCL BIT6
#define SDA BIT7

void init_P1(void);
void init_I2C(volatile unsigned int slave_address);
void init_AD(void);
void Transmit(unsigned char data[], unsigned int len);

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	init_P1();
	init_AD();
	init_I2C(0xAD);
	_BIS_SR(LPM0_bits | GIE);
	return 0;
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

void init_P1(void)
{
	P1OUT &= ~LED;
	P1DIR |= LED;
}

void init_AD(void)
{
	ADC10AE0  = AD_IN;
	ADC10CTL0 = SREF_0 + ADC10SHT_0 + ADC10IE + ADC10ON;
	ADC10CTL1 = AD_INCH + SHS_0 + ADC10DIV_0 + ADC10SSEL_3 + CONSEQ_0;
}

interrupt(USCIAB0TX_VECTOR) USCIAB0TX_ISR(void)
{
	unsigned int d = 1023;
	unsigned char d_send[2];
	P1OUT |= LED;
	if(IFG2 & UCB0RXIFG)
	{
		if(UCB0RXBUF==0x55)
		{
			ADC10CTL0 |= ENC+ADC10SC;
			while( (ADC10CTL0 & ADC10IFG) == 0);
			d = ADC10MEM;
			d_send[0] = d & 0xff;
			d_send[1] = d>>8;
			while( (UCB0STAT & UCSTTIFG)==0);
			Transmit(d_send, 2);
			UCB0STAT &= ~(UCSTPIFG | UCSTTIFG);
		}
		P1OUT &= ~LED;	
	}
	IFG2 &= ~(UCB0TXIFG|UCB0RXIFG);
}

/*interrupt(USCIAB0RX_VECTOR) USCIAB0RX_ISR(void)
{
	P1OUT |= LED;
	Atraso(1000);
	UCB0STAT &= ~(UCSTPIFG | UCSTTIFG);
	P1OUT &= ~LED;
}*/


