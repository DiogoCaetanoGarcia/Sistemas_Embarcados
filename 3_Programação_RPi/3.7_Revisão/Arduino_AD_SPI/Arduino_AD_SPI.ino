#include <SPI.h>

volatile char receivedData = 0;
int sensorValue;

ISR (SPI_STC_vect)
{
  receivedData = SPDR;
}

void setup()
{
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPDR = 0xAA;
  SPI.attachInterrupt();
}

void loop()
{
  switch(receivedData)
  {
    case 0x55:
      sensorValue = analogRead(A0);
      SPDR = sensorValue & 0xFF;
      receivedData = 0;
      break;
    case 0x1:
      SPDR = sensorValue >> 8;
      receivedData = 0;
      break;
    case 0x2:
      SPDR = 0xAA;
      receivedData = 0;
      break;
  }
}
