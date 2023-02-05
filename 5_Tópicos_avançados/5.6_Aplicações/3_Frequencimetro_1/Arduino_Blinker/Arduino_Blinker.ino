const int ledPin = LED_BUILTIN;  // the number of the LED pin
unsigned long t0[] = {0,0};
unsigned long interval1 = 500;
unsigned long interval2 = 5000;

void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  unsigned long t1 = millis();

  if(t1 - t0[1] >= interval2)
  {
    interval1 /= 2;
    if(interval1<1)
      interval1 = 500;
    t0[1] = t1;
  }
  if (t1 - t0[0] >= interval1)
  {
    t0[0] = t1;
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}
