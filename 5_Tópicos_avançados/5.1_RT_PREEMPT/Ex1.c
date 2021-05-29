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
	unsigned int logindex=0;
	int val = 0;
	pin0 = init_gpio(PIN_VALUE);
	signal(SIGINT, dumptimestamps);
	while(1)
	{
		usleep(DELAY_US);
		setiopin(pin0,val);
		INC_CNT(logindex, MAX_LOGENTRIES);
		INC_CNT(val, 2);
		logtimestamp(&t[logindex]);
	}
}
