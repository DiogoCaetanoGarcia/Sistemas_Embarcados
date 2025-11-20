#ifndef _RT_LIB_H_
#define _RT_LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/mman.h>
#include <limits.h>
#include <sched.h>
#include <wiringPi.h>

#define PIN_VALUE 7
#define MAX_LOGENTRIES 5000

#define DELAY_US 1000
#define DELAY_NS (DELAY_US*1000)

//extern struct timespec t[MAX_LOGENTRIES];

void logtimestamp(struct timespec *log_t);
void panic(char *message);
void init_gpio(int gpioport);
void setiopin(int gpioport, int val);
void end_gpio(int gpioport);
void sleep_until(struct timespec *ts, int delay);
void dumptimestamps(struct timespec *t);

#endif //_RT_LIB_H_
