const int buttonPin = 2;
int blinkCount = 0;
const int blinkT = 500;

void blink(int num_blinks, int period)
{
  while(num_blinks--)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(period/2);
    digitalWrite(LED_BUILTIN, LOW);
    delay(period/2);
  }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);      // set LED pin as output
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(LED_BUILTIN, LOW);    // switch off LED pin
  Serial.begin(9600);            // initialize UART with baud rate of 9600
}

void loop() {
  if(Serial.available())
  {
    char receivedData = Serial.read();
    if ((receivedData>0)&&(receivedData<6))
    {
      blink(receivedData, blinkT);
      Serial.write(receivedData);
    }
  }
  if(digitalRead(buttonPin)==0)
  {
    while(digitalRead(buttonPin)==0);
    blinkCount = (blinkCount+1)%6;
    blink(blinkCount, blinkT);
    Serial.write(blinkCount);
  }
}
