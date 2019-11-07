#include "freq.h"

int main(void)
{
	wiringPiSetup();
	Config_Pins();
	Config_LCD();
	while(1)
	{
		Clear_LCD();
		Send_String("Ola");
		usleep(250000);
		Clear_LCD();
		Send_String("Mundo!");
		usleep(250000);
	}
	return 0;
}
