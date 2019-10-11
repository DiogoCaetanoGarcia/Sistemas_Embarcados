#include <wiringPi.h>
#include <unistd.h>
#define SAIDA 7

void sqwv(int freq_hz)
{
	int T_us_2 = (500000 + (freq_hz/2))/freq_hz;
	while(1)
		{
			digitalWrite(SAIDA, HIGH);
			usleep(T_us_2);
			digitalWrite(SAIDA, LOW);
			usleep(T_us_2);
		}
}


int main(void)
{
	wiringPiSetup();
	pinMode(SAIDA, OUTPUT);
	sqwv(1000);
	return 0;
}
