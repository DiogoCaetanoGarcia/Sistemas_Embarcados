#include <msp430g2553.h>
#include <legacymsp430.h>

#define LED BIT0

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD;	// Stop WDT
	
	BCSCTL1 = CALBC1_1MHZ;		//MCLK e SMCLK @ 1MHz
	DCOCTL = CALDCO_1MHZ;		//MCLK e SMCLK @ 1MHz
	P1OUT &= ~LED;
	P1DIR |= LED;
	TA0CCR0 = 62500-1; //10000-1;
	TA0CTL = TASSEL_2 + ID_3 + MC_1 + TAIE;
	_BIS_SR(LPM0_bits+GIE);
	return 0;
}

interrupt(TIMER0_A1_VECTOR) TA0_ISR(void)
{
	static int cnt = 0;
    int cs[] = {
    	10,    // 10
        30,    // 10+20
		70,    // 10+20+40
		150,   // 10+20+40+80
		310,   // 10+20+40+80+160
		630,   // 10+20+40+80+160+320
		1270,  // 10+20+40+80+160+320+640
		2550}; // 10+20+40+80+160+320+640+1280
	int i;

	cnt++;
	for(i=0; i<7; i++)
	{
		if(cnt==cs[i])
		{
			TA0CCR0 = (TA0CCR0+1)/2-1;
		}
	}
	if(cnt==cs[7])
	{
		TA0CCR0 = 62500-1;
		cnt = 0;
	}
	P1OUT ^= LED;
	TA0CTL &= ~TAIFG;
}
