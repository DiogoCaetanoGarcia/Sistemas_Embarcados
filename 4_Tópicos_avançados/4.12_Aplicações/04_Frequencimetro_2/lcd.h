#ifndef _LCD_H_
#define _LCD_H_

#include <wiringPi.h> // pinMode() e digitalWrite()
#include <unistd.h> // usleep()

#define EN 7
#define RS 0
#define D4 3
#define D5 4
#define D6 5
#define D7 6
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
