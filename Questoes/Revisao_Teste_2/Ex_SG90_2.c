#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SAIDA 7

int main(void)
{
	int i, t = 2000;
	wiringPiSetup();
	pinMode(SAIDA, OUTPUT);
	for(i=0; i<25; i++)
	{
		digitalWrite(SAIDA, HIGH);
		usleep(t);
		digitalWrite(SAIDA, LOW);
		usleep(20000-t);
	}
	t = 1000;
	for(i=0; i<25; i++)
        {
                digitalWrite(SAIDA, HIGH);
                usleep(t);
                digitalWrite(SAIDA, LOW);
                usleep(20000-t);
        }
	return 0;
}
