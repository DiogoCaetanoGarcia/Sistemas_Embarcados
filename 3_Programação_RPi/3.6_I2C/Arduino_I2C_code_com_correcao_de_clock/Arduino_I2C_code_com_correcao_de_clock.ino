#include <Wire.h>

const int ledPin = 2;
const int blinkT = 500;
unsigned char receivedData = 1;
unsigned char sentData = 1;

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

void setup()
{
  CLKPR = 0x80;
  CLKPR = 0x01;
  Wire.begin(0xF);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  if((receivedData>0)&&(receivedData<6))
  {
    sentData = receivedData;
    blink(ledPin, sentData, blinkT);
    receivedData = 0;
  }
}

void receiveEvent(int receivedBytes)
{
  receivedData = Wire.read();
}

void requestEvent()
{
  Wire.write(sentData);
}
