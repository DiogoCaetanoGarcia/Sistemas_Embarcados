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
// pthread_attr_setschedparam(). A memoria deste programa eh 'presa'
// chamando a funcao mlockall().
//
// Este ultimo ponto eh necessario porque o Linux separa a memoria
// RAM em paginas, e armazena paginas menos utilizadas no disco
// rigido (swap space). Se outro programa consumir mais memoria do
// que o este programa, o Linux podera salvar a memoria deste programa
// no swap space, atrasando sua performance.
// (Ref.: https://www.linux.com/news/all-about-linux-swap-space)


#include "rt_lib.h"

#define test_pthread_call(ret, s) if(ret){printf(s); return ret;}

void *thread_func(void *data)
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
	return NULL;
}

int main(int argc, char* argv[])
{
	struct sched_param param;
	pthread_attr_t attr;
	pthread_t thread;
	int ret;

	/* Lock memory */
	if(mlockall(MCL_CURRENT|MCL_FUTURE) == -1) {
		printf("mlockall failed: %m\n");
		return -2;
	}

	/* Initialize pthread attributes (default values) */
	ret = pthread_attr_init(&attr);
	if (ret) {
		printf("init pthread attributes failed\n");
		return ret;
	}

	/* Set a specific stack size  */
	ret = pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
	if (ret) {
		printf("pthread setstacksize failed\n");
		return ret;
	}

	/* Set scheduler policy and priority of pthread */
	ret = pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
	if (ret) {
		printf("pthread setschedpolicy failed\n");
		return ret;
	}
	param.sched_priority = 99;
	ret = pthread_attr_setschedparam(&attr, &param);
	if (ret) {
		printf("pthread setschedparam failed\n");
		return ret;
	}
	/* Use scheduling parameters of attr */
	ret = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
	if (ret) {
		printf("pthread setinheritsched failed\n");
		return ret;
	}

	/* Create a pthread with specified attributes */
	ret = pthread_create(&thread, &attr, thread_func, NULL);
	if (ret) {
		printf("create pthread failed\n");
		return ret;
	}

	pthread_getschedparam(thread, &ret, &param);
	printf("policy = %d, sched_priority = %d\n", ret, param.sched_priority);

	/* Join the thread and wait until it is done */
	ret = pthread_join(thread, NULL);
	if (ret) {
		printf("join pthread failed: %m\n");
		return ret;
	}

	return ret;
}




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
