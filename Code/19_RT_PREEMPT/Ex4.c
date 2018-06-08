// Este codigo gera uma onda quadrada de 500 Hz
// no pino PIN_VALUE (definido em "rt_lib.h").
// A cada 1 ms, o pino eh invertido.
//
// Aperte CTRL-C durante a execucao do programa para para-lo,
// e confira a temporizacao do sistema lendo o arquivo
// "dumpfile.txt".
//
// A temporizacao eh feita chamando a funcao sleep_until(),
// que por sua vez chama a funcao clock_nanosleep(). A prioridade
// de execucao deste programa eh definida chamando a funcao
// pthread_setschedparam(). A memoria deste programa eh 'presa'
// chamando a funcao mlockall().

// Este ultimo ponto eh necessario porque o Linux separa a memoria
// RAM em paginas, e armazena paginas menos utilizadas no disco
// rigido (swap space). Se outro programa consumir mais memoria do
// que o este programa, o Linux podera salvar a memoria deste programa
// no swap space, atrasando sua performance.
// (Ref.: https://www.linux.com/news/all-about-linux-swap-space)
//
// Para conferir o efeito da priorizacao deste programa, acesse o
// Raspberry Pi remotamente em uma sessao separada, e veja o efeito
// sobre a onda quadrada.
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
	struct sched_param sp;
	struct timespec ts;
	unsigned int logindex=0;
	int val = 0;
	pin0 = init_gpio(PIN_VALUE);
	signal(SIGINT, dumptimestamps);
	clock_gettime(CLOCK_MONOTONIC, &ts);

	if(mlockall(MCL_FUTURE|MCL_CURRENT))
	{
		fprintf(stderr,"WARNING: Failed to lock memory\n");
	}

	sp.sched_priority = 99;
	if(pthread_setschedparam(pthread_self(), SCHED_FIFO, &sp))
	{
		fprintf(stderr,"WARNING: Failed to set stepper thread"
			"to real-time priority\n");
	}

	while(1)
	{
		sleep_until(&ts, DELAY_NS);
		setiopin(pin0,val);
		INC_CNT(logindex, MAX_LOGENTRIES);
		INC_CNT(val, 2);
		logtimestamp(&t[logindex]);
	}
}
