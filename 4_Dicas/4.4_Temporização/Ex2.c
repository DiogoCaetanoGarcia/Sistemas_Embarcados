#include <stdio.h>
#include <time.h>

#define LEN 150
int main ()
{
	char buf[LEN];
	time_t curtime;
	struct tm *loc_time;

	// Hora atual do sistema
	curtime = time(NULL);

	// Converte hora atual para estrutura tm
	loc_time = localtime (&curtime);

	// Apresenta data e hora em formato padrão
	printf("%s", asctime (loc_time));

	// Apresenta data e hora em formato
	// de escolha do programador
	strftime(buf, LEN,
		"Dia:  %A, %b %d\nHora: %I:%M %p",
		loc_time);
	puts(buf);

	return 0;
}