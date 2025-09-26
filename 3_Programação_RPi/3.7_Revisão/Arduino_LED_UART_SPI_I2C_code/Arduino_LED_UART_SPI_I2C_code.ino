#include <SPI.h>
#include <Wire.h>

const int ledPin = 2;
const int blinkT = 500;
const int buttonPin = 3;
int button_count = 0;
char rxUART = 0;
volatile char rxSPI = 0;
unsigned char rxI2C = 1;
unsigned char txI2C = 1;

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

ISR (SPI_STC_vect)
{
  rxSPI = SPDR;
}

void rx_I2C_event(int receivedBytes)
{
  rxI2C = Wire.read();
}

void tx_I2C_event()
{
  Wire.write(txI2C);
}

void setup()
{
  // UART
  Serial.begin(9600);            // initialize UART with baud rate of 9600
  // SPI
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);       //Turn on SPI in Slave Mode
  SPDR = 10;
  SPI.attachInterrupt();
  // I2C
  Wire.begin(0xF);
  Wire.onRequest(tx_I2C_event);
  Wire.onReceive(rx_I2C_event);
  // LED & button
  pinMode(ledPin, OUTPUT);      // set LED pin as output
  digitalWrite(ledPin, LOW);    // switch off LED pin
  pinMode(buttonPin, INPUT_PULLUP);
  blink(ledPin, 5, blinkT);
}

void loop() {
  // UART
  if(Serial.available())
  {
    rxUART = Serial.read();
    if ((rxUART>0)&&(rxUART<6))
    {
      blink(ledPin, rxUART, blinkT);
      Serial.write(rxUART);
    }
  }
  // SPI
  if ((rxSPI>0)&&(rxSPI<6))
  {
    blink(ledPin, rxSPI, blinkT);
    SPDR = rxSPI;
    rxSPI = 0;
  }
  // I2C
  if((rxI2C>0)&&(rxI2C<6))
  {
    txI2C = rxI2C;
    blink(ledPin, txI2C, blinkT);
    rxI2C = 0;
  }
  // Button
  if(digitalRead(buttonPin)==0)
  {
    while(digitalRead(buttonPin)==0);
    button_count = (button_count+1)%6;
    blink(ledPin, button_count, blinkT);
    Serial.write(button_count);
  }
}
