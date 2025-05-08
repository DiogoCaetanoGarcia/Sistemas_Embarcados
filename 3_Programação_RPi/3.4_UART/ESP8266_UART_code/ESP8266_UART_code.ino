const int buttonPin = 0;              // GPIO0 (atenção: não segure o botão no boot!)
const int ledPin = 2;                 // GPIO2 é o LED do ESP-01 (LED_BUILTIN pode ser 1 ou 2 dependendo do módulo)
int blinkCount = 0;
const int blinkT = 500;

void blink(int num_blinks, int period)
{
  while (num_blinks--)
  {
    digitalWrite(ledPin, HIGH);       // LED do ESP-01 acende em HIGH
    delay(period / 2);
    digitalWrite(ledPin, LOW);
    delay(period / 2);
  }
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);   // Usa o resistor pull-up interno
  digitalWrite(ledPin, LOW);          // Apaga o LED inicialmente
  Serial.begin(9600);                 // Porta Serial padrão do ESP8266
  blink(6, blinkT);                   // Sinal de boot
}

void loop()
{
  if (Serial.available())
  {
    char receivedData = Serial.read();
    if ((receivedData > 0) && (receivedData < 6))
    {
      blink(receivedData, blinkT);
      Serial.write(receivedData);
    }
  }

  if (digitalRead(buttonPin) == LOW)
  {
    while (digitalRead(buttonPin) == LOW);  // Debounce simples: espera soltar
    blinkCount = (blinkCount + 1) % 6;
    blink(blinkCount, blinkT);
    Serial.write(blinkCount);
  }
}
