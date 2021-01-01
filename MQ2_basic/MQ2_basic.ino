const int gaspin = A0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  Serial.println(analogRead(gaspin));
  delay(1000);
}

