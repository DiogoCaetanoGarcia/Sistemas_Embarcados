#include <Wire.h>

const int ledPin = 2;
const int blinkT = 500;
unsigned char receivedData = 1;
unsigned char sentData = 1;

void blink(int led_pin, int num_blinks, int period)
{
  while(num_blinks--)
  {
    digitalWrite(led_pin, HIGH);
    delay(period/2);
    digitalWrite(led_pin, LOW);
    delay(period/2);
  }
}

void setup()
{
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
