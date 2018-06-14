// Compile incluindo o arquivo gpio_sysfs.c, e execute como root:
//	gcc 01_Ola_LCD.c gpio_sysfs.c -o olalcd
//	sudo ./olalcd
//

#include "gpio_sysfs.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EN 4
#define RS 17
#define D4 22
#define D5 23
#define D6 24
#define D7 25
#define DADO 1
#define COMANDO 0

void Config_Pins(void)
{
	setGPIO_Out(EN);
	setGPIO_Out(RS);
	setGPIO_Out(D4);
	setGPIO_Out(D5);
	setGPIO_Out(D6);
	setGPIO_Out(D7);
}

void Free_Pins(void)
{
	unsetGPIO(EN);
	unsetGPIO(RS);
	unsetGPIO(D4);
	unsetGPIO(D5);
	unsetGPIO(D6);
	unsetGPIO(D7);
}

char Send_Nibble(char nibble, char nibble_type)
{
	if((nibble_type!=DADO)&&(nibble_type!=COMANDO))
		return -1;
	GPIO_Write(EN, 1);
	GPIO_Write(RS, nibble_type);
	GPIO_Write(D4, nibble&1);
	GPIO_Write(D5, (nibble>>1)&1);
	GPIO_Write(D6, (nibble>>2)&1);
	GPIO_Write(D7, (nibble>>3)&1);
	GPIO_Write(EN, 0);
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
	Free_Pins();
	return 0;
}
