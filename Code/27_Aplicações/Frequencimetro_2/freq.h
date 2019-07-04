#ifndef _FREQ_H_
#define _FREQ_H_

#include <stdio.h>
#include <string.h>
// #include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
#include "lcd.h"

// Usar GPIO Pino 4, que é Pino 7 na wiringPi
#define PINO_ENT 7
#define T_AMOSTRAGEM 1000000000ul

struct freq_calc
{
	unsigned long contagem_eventos;
	struct timespec t[2];
};

extern struct freq_calc fc;

void config_freq(void);
void conta_eventos(void);
void sleep_until(unsigned long delay);
void calc_freq(void);

#endif // _FREQ_H_
