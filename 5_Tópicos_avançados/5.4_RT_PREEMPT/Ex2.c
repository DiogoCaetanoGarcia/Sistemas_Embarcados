// Este codigo gera uma onda quadrada de 500 Hz
// no pino PIN_VALUE (definido em "rt_lib.h").
// A cada 1 ms, o pino eh invertido.
//
// Aperte CTRL-C durante a execucao do programa para para-lo,
// e confira os valores de média e de desvio-padrão da
// temporizacao do sistema.
//
// A temporizacao eh feita chamando a funcao sleep_until(),
// que por sua vez chama a funcao clock_nanosleep().
// Enquanto usleep() (e seus irmaos sleep() e nanosleep())
// garantem um atraso MINIMO (mas nao um maximo),
// clock_nanosleep() calcula o tempo comparando o tempo atual
// com um tempo absoluto, fornecendo maior precisao no atraso.

#include "rt_lib.h"

int main(void)
{
	struct timespec t[MAX_LOGENTRIES];
	struct timespec ts;

	init_gpio(PIN_VALUE);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	for(unsigned int logindex=0; logindex<MAX_LOGENTRIES; logindex++)
	{
		sleep_until(&ts, DELAY_NS);
		setiopin(PIN_VALUE, logindex%2);
		logtimestamp(&t[logindex]);
	}
	dumptimestamps(t);
	end_gpio(PIN_VALUE);
	return 0;
}
