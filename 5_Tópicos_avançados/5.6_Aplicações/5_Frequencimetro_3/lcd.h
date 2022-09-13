#ifndef _LCD_H_
#define _LCD_H_

#include <pigpio.h> // gpioSetMode() e gpioWrite()
#include <unistd.h> // usleep()

#define EN 4
#define RS 17
#define D4 22
#define D5 23
#define D6 24
#define D7 25
#define DADO 1
#define COMANDO 0

void Config_Pins(void);
char Send_Nibble(char nibble, char nibble_type);
char Send_Byte(char byte, char byte_type);
void Clear_LCD(void);
void Config_LCD(void);
void Send_String(char *str);
void Send_Int(int x);
void Send_Double(double x, int decimal_places);

#endif // _LCD_H_
