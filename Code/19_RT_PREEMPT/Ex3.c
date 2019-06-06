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
// pthread_attr_setschedparam().

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

	//pthread_getschedparam(thread, &ret, &param);
	//printf("policy = %d, sched_priority = %d\n", ret, param.sched_priority);

	/* Join the thread and wait until it is done */
	ret = pthread_join(thread, NULL);
	if (ret) {
		printf("join pthread failed: %m\n");
		return ret;
	}

	return ret;
}
