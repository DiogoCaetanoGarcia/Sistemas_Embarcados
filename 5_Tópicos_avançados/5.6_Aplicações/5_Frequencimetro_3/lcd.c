#include "lcd.h"

void Config_Pins(void)
{
	gpioSetMode(EN, PI_OUTPUT);
	gpioSetMode(RS, PI_OUTPUT);
	gpioSetMode(D4, PI_OUTPUT);
	gpioSetMode(D5, PI_OUTPUT);
	gpioSetMode(D6, PI_OUTPUT);
	gpioSetMode(D7, PI_OUTPUT);
}

char Send_Nibble(char nibble, char nibble_type)
{
	if((nibble_type!=DADO)&&(nibble_type!=COMANDO))
		return -1;
	gpioWrite(EN, 1);
	gpioWrite(RS, nibble_type);
	gpioWrite(D4, nibble&1);
	gpioWrite(D5, (nibble>>1)&1);
	gpioWrite(D6, (nibble>>2)&1);
	gpioWrite(D7, (nibble>>3)&1);
	gpioWrite(EN, 0);
	usleep(500);
	return 0;
}

char Send_Byte(char byte, char byte_type)
{
	if(Send_Nibble(byte>>4, byte_type)==-1)
		return -1;
	Send_Nibble(byte & 0xF, byte_type);
	return 0;
}

void Clear_LCD(void)
{
	Send_Byte(0x01, COMANDO);
	usleep(20000);
	Send_Byte(0x02, COMANDO);
	usleep(20000);
}

void Config_LCD(void)
{
	usleep(10000);
	Config_Pins();
	Send_Nibble(0x3, COMANDO);
	Send_Nibble(0x3, COMANDO);
	Send_Nibble(0x3, COMANDO);
	Send_Nibble(0x2, COMANDO);
	Send_Byte(0x20, COMANDO);
	Send_Byte(0x14, COMANDO);
	Send_Byte(0x0C, COMANDO);
	Send_Byte(0x06, COMANDO);
	Clear_LCD();
}

void Send_String(char *str)
{
	int i = 0;
	while(str[i]!=0)
	{
		Send_Byte(str[i], DADO);
		i++;
	}
}

void Send_Int(int x)
{
	char buffer[16];
	snprintf(buffer, sizeof(buffer), "%d", x);
	Send_String(buffer);
}

void Send_Double(double x, int decimal_places)
{
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "%.*f", decimal_places, x);
	Send_String(buffer);
}

