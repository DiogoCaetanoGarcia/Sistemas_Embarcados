#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	struct tm strtime;
	time_t timeoftheday;

	timeoftheday = time(NULL);
	printf("Data atual:\n   %s", ctime(&timeoftheday));

	puts("Setando estrutura para\n   04/02/2010, 03:30:38");
	strtime.tm_year = 2010-1900; // Anos desde 1900
	strtime.tm_mon = 1; // Meses desde janeiro, 0-11
	strtime.tm_mday = 4;
	strtime.tm_hour = 02; // Horas desde meia-noite, 0-23
	strtime.tm_min = 30;
	strtime.tm_sec = 38;
	strtime.tm_isdst = 0;
	timeoftheday = mktime(&strtime);
	printf("Tempo retornado:\n   %s", ctime(&timeoftheday));
	printf("Conferindo resultado\n   com programa 'cal'\n\n");
	system("cal 2 2010");
	return 0;
}