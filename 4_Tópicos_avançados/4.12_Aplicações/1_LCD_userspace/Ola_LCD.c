// Compile incluindo o arquivo gpio_sysfs.c, e execute como root:
//	gcc 01_Ola_LCD.c gpio_sysfs.c -o olalcd
//	sudo ./olalcd
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

#define EN      7 // wiringPi#, BCM #4
#define RS      0 // wiringPi#, BCM #17
#define D4      3 // wiringPi#, BCM #22
#define D5      4 // wiringPi#, BCM #23
#define D6      5 // wiringPi#, BCM #24
#define D7      6 // wiringPi#, BCM #25
#define DADO    1
#define COMANDO 0

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
	wiringPiSetup();
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

//Compile junto com o arquivo gpio_sysfs.c
int main()
{
	char str[200] = "OLA LCD!";

	Config_LCD();
	do
	{
		Clear_LCD();
		Send_String(str);
		puts("Digite uma palavra (EXIT para sair):");
		scanf("%s", str);
	}while(strcmp(str,"EXIT")!=0);
	return 0;
}
