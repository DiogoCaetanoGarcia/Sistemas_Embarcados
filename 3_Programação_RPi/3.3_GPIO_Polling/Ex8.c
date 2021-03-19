#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

int i_global = 0;
int pin = 7;

void interrupcao(void)
{
	puts("Executando a interrupção...");
	// Se lermos um 0 nos próximos 100us,
	// consideramos que foi um bounce
	for(int i=0; i<1000; i++)
	{
		if(digitalRead(pin)==0)
			return;
		usleep(100);
	}
	i_global++;
	printf("Botao solto, i_global = %d\n", i_global);
}

int main(void)
{
	wiringPiSetup();
	pinMode(pin, INPUT);
	wiringPiISR(pin, INT_EDGE_RISING, &interrupcao) ;
	puts("Pressione o botao");
	while(i_global<15)
	{
		sleep(1);
		puts("Loop principal");
	}
	return 0;
}
