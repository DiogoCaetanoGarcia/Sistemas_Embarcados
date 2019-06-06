// Este codigo gera uma onda quadrada de 500 Hz
// no pino PIN_VALUE (definido em "rt_lib.h").
// A cada 1 ms, o pino eh invertido.
//
// Aperte CTRL-C durante a execucao do programa para para-lo,
// e confira a temporizacao do sistema lendo o arquivo
// "dumpfile.txt".
//
// A temporizacao eh feita chamando a funcao sleep_until(),
// que por sua vez chama a funcao clock_nanosleep().
// Enquanto usleep() (e seus irmaos sleep() e nanosleep())
// garantem um atraso MINIMO (mas nao um maximo),
// clock_nanosleep() calcula o tempo comparando o tempo atual
// com um tempo absoluto, fornecendo maior precisao no atraso.
//
// Para conferir este efeito, acesse o Raspberry Pi remotamente
// em uma sessao separada, e veja o efeito sobre a onda quadrada.
//
// Outra opcao eh executar
//
//    cat /dev/zero > /dev/null
//
// que continuamente joga o valor 0 no dispositivo
// 'null', que ignora qualquer caracter escrito nele.
// Isto vai basicamente tomar tempo de processamento da CPU e
// gastar espaco em memoria. Aperte CTRL-C para parar o processo.
//
// Outra opcao eh fazer pings continuos para o Raspberry pi, executando
//
//    ping IP_DO_RASPBERRY_PI
//
// em outra maquina. Aperte CTRL-C para parar o processo.

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
