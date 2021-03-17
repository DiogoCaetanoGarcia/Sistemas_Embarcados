#include <wiringPi.h>
#include <unistd.h>

int main()
{
	int pin = 7; // Pino GPIO4 é o 7 na WiringPi
	wiringPiSetup();
	pinMode(pin, OUTPUT);
	digitalWrite(pin, HIGH);
	sleep(5);
	digitalWrite(pin, LOW);
	return 0;
}
