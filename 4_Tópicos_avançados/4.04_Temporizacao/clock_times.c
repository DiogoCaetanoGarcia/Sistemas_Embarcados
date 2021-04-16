/* clock_times.c
   Licensed under GNU General Public License v2 or later.
*/
#define _XOPEN_SOURCE 600
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define SECS_IN_DAY (24 * 60 * 60)

static void
displayClock(clockid_t clock, const char *name, bool showRes)
{
	struct timespec ts;
	if (clock_gettime(clock, &ts) == -1)
	{
		perror("clock_gettime");
		exit(EXIT_FAILURE);
	}

	printf("%-15s: %10jd.%03ld (", name,
		(intmax_t) ts.tv_sec, ts.tv_nsec / 1000000);

	long days = ts.tv_sec / SECS_IN_DAY;
	if (days > 0)
		printf("%ld days + ", days);

	printf("%2dh %2dm %2ds",
		(int) (ts.tv_sec % SECS_IN_DAY) / 3600,
		(int) (ts.tv_sec % 3600) / 60,
		(int) ts.tv_sec % 60);
	printf(")\n");

	if (clock_getres(clock, &ts) == -1)
	{
		perror("clock_getres");
		exit(EXIT_FAILURE);
	}

	if (showRes)
		printf("     resolution: %10jd.%09ld\n",
			(intmax_t) ts.tv_sec, ts.tv_nsec);
}

int main(int argc, char *argv[])
{
	bool showRes = 1; //argc > 1;

	displayClock(CLOCK_REALTIME, "CLOCK_REALTIME", showRes);
#ifdef CLOCK_TAI
	displayClock(CLOCK_TAI, "CLOCK_TAI", showRes);
#endif
	displayClock(CLOCK_MONOTONIC, "CLOCK_MONOTONIC", showRes);
#ifdef CLOCK_BOOTTIME
	displayClock(CLOCK_BOOTTIME, "CLOCK_BOOTTIME", showRes);
#endif
	exit(EXIT_SUCCESS);
}
