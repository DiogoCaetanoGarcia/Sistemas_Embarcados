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
	struct timespec ts;
	unsigned int logindex=0;
	int val = 0;
	pin0 = init_gpio(PIN_VALUE);
	signal(SIGINT, dumptimestamps);
	clock_gettime(CLOCK_MONOTONIC, &ts);
	while(1)
	{
		sleep_until(&ts, DELAY_NS);
		setiopin(pin0,val);
		INC_CNT(logindex, MAX_LOGENTRIES);
		INC_CNT(val, 2);
		logtimestamp(&t[logindex]);
	}
}
