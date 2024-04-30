#include <SPI.h>

const int ledPin = 2;
const int blinkT = 500;
volatile char receivedData = 0;

void blink(int led_pin, int num_blinks, int period)
{
  unsigned long t = millis();
  period /= 2;
  while(num_blinks--)
  {
    digitalWrite(led_pin, HIGH);
    while((millis()-t)<period);
    t += period;
    digitalWrite(led_pin, LOW);
    while((millis()-t)<period);
    t += period;
  }
}

ISR (SPI_STC_vect)
{
  receivedData = SPDR;
}

void setup()
{
  CLKPR = 0x80;
  CLKPR = 0x01;
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);       //Turn on SPI in Slave Mode
  SPDR = 10;
  SPI.attachInterrupt();
  pinMode(ledPin, OUTPUT);      // set LED pin as output
  digitalWrite(ledPin, LOW);    // switch off LED pin
  blink(ledPin, 5, blinkT);
}

void loop()
{
  if ((receivedData>0)&&(receivedData<6))
  {
    blink(ledPin, receivedData, blinkT);
    SPDR = receivedData;
    receivedData = 0;
  }
}
