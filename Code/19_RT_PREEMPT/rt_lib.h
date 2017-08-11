#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/mman.h>
#include <signal.h>

#define INC_CNT(CNT, MAX_CNT) CNT=(CNT+1)%(MAX_CNT)

#define PIN_VALUE 4
#define MAX_LOGENTRIES 2000

#define DELAY_US 1000
#define DELAY_NS (DELAY_US*1000)

extern struct timespec t[MAX_LOGENTRIES];
extern FILE *pin0;

void logtimestamp(struct timespec *log_t);
void panic(char *message);
FILE *init_gpio(int gpioport);
void setiopin(FILE *fp, int val);
void end_gpio(int gpioport, FILE* fp);
void sleep_until(struct timespec *ts, int delay);
void dumptimestamps(int unused);