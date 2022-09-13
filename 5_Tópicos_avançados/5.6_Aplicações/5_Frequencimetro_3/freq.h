#ifndef _FREQ_H_
#define _FREQ_H_

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
#include <pigpio.h>
#include <time.h>
#include "lcd.h"

#define PINO_ENT     27
#define SEC_N        1000000000ul
#define T_AMOSTRAGEM SEC_N

struct freq_calc
{
	unsigned long contagem_eventos;
	struct timespec t[2];
};

extern struct freq_calc fc;

void config_freq(void);
void conta_eventos(int gpio, int level, uint32_t tick);
void sleep_until(unsigned long delay);
void calc_freq(void);

#endif // _FREQ_H_
