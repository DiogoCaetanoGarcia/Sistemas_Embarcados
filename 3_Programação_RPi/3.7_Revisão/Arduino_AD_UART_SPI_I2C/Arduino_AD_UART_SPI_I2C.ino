#include <Wire.h>
#include <SPI.h>

// I2C
volatile char receivedDataI2C = 0;
char sentDataI2C[2];
int sensorValueI2C;
void receiveEvent(int receivedBytes)
{
  receivedDataI2C = Wire.read();
}
void requestEvent()
{
  Wire.write(sentDataI2C, 2);
}

// SPI
volatile char receivedDataSPI = 0;
int sensorValueSPI;
ISR (SPI_STC_vect)
{
  receivedDataSPI = SPDR;
}

// UART
int sensorValueUART;
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
  // I2C
  if(receivedDataI2C == 0x55)
  {
    sensorValueI2C = analogRead(A0);
    sentDataI2C[0] = sensorValueI2C & 0xFF;
    sentDataI2C[1] = sensorValueI2C >> 8;
    receivedDataI2C = 0;
  }
  // SPI
  switch(receivedDataSPI)
  {
    case 0x55:
      sensorValueSPI = analogRead(A0);
      SPDR = sensorValueSPI & 0xFF;
      receivedDataSPI = 0;
      break;
    case 0x1:
      SPDR = sensorValueSPI >> 8;
      receivedDataSPI = 0;
      break;
    case 0x2:
      SPDR = 0xAA;
      receivedDataSPI = 0;
      break;
  }
  // UART
  if((millis()-t_UART)>=10)
  {
    t_UART = millis();
    sensorValueUART = analogRead(A0);
    Serial.write(sensorValueUART & 0xFF);
    Serial.write(sensorValueUART >> 8);
  }
}
