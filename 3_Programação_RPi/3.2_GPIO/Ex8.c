#include <stdio.h>
#include <wiringPi.h>

int main(void)
{
	int i = 0, pin = 7;
	wiringPiSetup();
	pinMode(pin, INPUT);
	while(i<15)
	{
		printf("i = %d\n", i);
		puts("Pressione o botao");
		while(digitalRead(pin));
		puts("Botao pressionado");
		while(digitalRead(pin)==0);
		puts("Botao solto");
		i++;
	}
	return 0;
}
