// Este codigo gera uma onda quadrada de 500 Hz
// no pino PIN_VALUE (definido em "rt_lib.h").
// A cada 1 ms, o pino eh invertido.
//
// Aperte CTRL-C durante a execucao do programa para para-lo,
// e confira os valores de média e de desvio-padrão da
// temporizacao do sistema.
//
// A temporizacao eh feita chamando a funcao usleep(),
// que nao garante o atraso com grande precisao, pois
// outros processos interferem na temporizacao.

#include "rt_lib.h"

int main(void)
{
	struct timespec t[MAX_LOGENTRIES];
	init_gpio(PIN_VALUE);
	for(unsigned int logindex=0; logindex<MAX_LOGENTRIES; logindex++)
	{
		usleep(DELAY_US);
		setiopin(PIN_VALUE, logindex%2);
		logtimestamp(&t[logindex]);
	}
	dumptimestamps(t);
	end_gpio(PIN_VALUE);
	return 0;
}
