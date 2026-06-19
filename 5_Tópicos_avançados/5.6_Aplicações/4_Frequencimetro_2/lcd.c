#include "lcd.h"

void Config_Pins(void)
{
	pinMode(EN, OUTPUT);
	pinMode(RS, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinMode(D7, OUTPUT);
}

char Send_Nibble(char nibble, char nibble_type)
{
	if((nibble_type!=DADO)&&(nibble_type!=COMANDO))
		return -1;
	digitalWrite(EN, 1);
	digitalWrite(RS, nibble_type);
	digitalWrite(D4, nibble&1);
	digitalWrite(D5, (nibble>>1)&1);
	digitalWrite(D6, (nibble>>2)&1);
	digitalWrite(D7, (nibble>>3)&1);
	digitalWrite(EN, 0);
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
