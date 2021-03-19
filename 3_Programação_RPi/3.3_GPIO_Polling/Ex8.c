#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

int i_global = 0;
int pin = 7;

void interrupcao(void);

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

void interrupcao(void)
{
	puts("Executando a interrupção");
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

#define N 128

void debounce_rising(int pin_val)
{
	int vals[N], s=0, pos=0, prev_val;
	for(int i=0; i<N; i++)
	{
		vals[i] = 0;
	}
	do
	{
		prev_val = vals[pos];
		vals[pos] = digitalRead(pin_val);
		s = s - prev_val + vals[pos];
		pos = (pos+1)%N;
	} while(s<(N/4));
}

void debounce_falling(int pin_val)
{
	int vals[N], s=N, pos=0, prev_val;
	for(int i=0; i<N; i++)
	{
		vals[i] = 1;
	}
        do
        {
                prev_val = vals[pos];
                vals[pos] = digitalRead(pin_val);
                s = s - prev_val + vals[pos];
                pos = (pos+1)%N;
        } while(s>(3*N/4));
}
