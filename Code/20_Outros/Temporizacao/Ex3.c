#include <stdio.h>
#include <time.h>

#define LEN 150
int main ()
{
	char buf[LEN];
	time_t curtime;
	struct tm *loc_time;

	//Getting current time of system
	curtime = time (NULL);

	// Converting current time to local time
	loc_time = localtime (&curtime);

	// Displaying date and time in standard format
	printf("%s", asctime (loc_time));

	strftime (buf, LEN, "Dia:  %A, %b %d.\n", loc_time);
	fputs (buf, stdout);
	strftime (buf, LEN, "Hora: %I:%M %p.\n", loc_time);
	fputs (buf, stdout);

	return 0;
}