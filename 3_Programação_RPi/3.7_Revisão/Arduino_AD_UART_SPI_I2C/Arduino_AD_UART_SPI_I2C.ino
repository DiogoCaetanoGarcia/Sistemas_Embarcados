#include <Wire.h>
#include <SPI.h>

// I2C
char sentDataI2C[2];
void receiveEvent(int receivedBytes)
{
  if(Wire.read() == 0x55)
  {
    int sensorValueI2C = analogRead(A0);
    sentDataI2C[0] = sensorValueI2C & 0xFF;
    sentDataI2C[1] = sensorValueI2C >> 8;
  }
}
void requestEvent()
{
  Wire.write(sentDataI2C, 2);
}

// SPI
int sensorValueSPI;
ISR (SPI_STC_vect)
{
  switch(SPDR)
  {
    case 0x55:
      sensorValueSPI = analogRead(A0);
      SPDR = sensorValueSPI & 0xFF;
      break;
    case 0x1:
      SPDR = sensorValueSPI >> 8;
      break;
    case 0x2:
      SPDR = 0xAA;
      break;
  }
}

// UART
unsigned long int t_UART = 0;

void setup()
{
  // I2C
  Wire.begin(0xF);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  // SPI
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPDR = 0xAA;
  SPI.attachInterrupt();
  // UART
  Serial.begin(9600);
  t_UART = millis();
}

void loop()
{
  unsigned long int cur_t = millis();
  if((cur_t - t_UART)>=10)
  {
    t_UART = cur_t;
    int sensorValueUART = analogRead(A0);
    Serial.write(sensorValueUART & 0xFF);
    Serial.write(sensorValueUART >> 8);
  }
}