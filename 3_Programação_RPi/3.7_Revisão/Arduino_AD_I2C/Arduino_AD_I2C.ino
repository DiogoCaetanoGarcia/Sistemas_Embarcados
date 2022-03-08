#include <Wire.h>

volatile char receivedData = 0;
char sentData[2];

void setup()
{
  Wire.begin(0xF);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}

void loop()
{
  if(receivedData == 0x55)
  {
    int sensorValue = analogRead(A0);
    sentData[0] = sensorValue & 0xFF;
    sentData[1] = sensorValue >> 8;
    receivedData = 0;
  }
}

void receiveEvent(int receivedBytes)
{
  receivedData = Wire.read();
}

void requestEvent()
{
  Wire.write(sentData, 2);
}
