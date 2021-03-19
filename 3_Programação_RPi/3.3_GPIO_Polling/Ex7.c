#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>

int i_global = 0;

void interrupcao(void)
{
	i_global++;
	printf("Botao pressionado, i_global = %d\n", i_global);
}

int main(void)
{
	int pin = 7;
	wiringPiSetup();
	pinMode(pin, INPUT);
	wiringPiISR(pin, INT_EDGE_FALLING, &interrupcao) ;
	puts("Pressione o botao");
	while(i_global<15)
	{
                sleep(1);
                printf("Loop principal, i_global = %d\n", i_global);
        }
	return 0;
}
