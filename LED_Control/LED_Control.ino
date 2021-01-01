char val, a, b;

void setup() {
  pinMode(13, OUTPUT);
 Serial.begin(9600);

}

void loop() {
  
if (Serial.available())
{
 //int val = Serial.parseInt();
 val = Serial.read();
  if( val == 'a')
  //if (val == 1)
  {
  digitalWrite(13, HIGH);
  Serial.println("HIGH");
  }

  else if (val == 'b')
  //if (val == 2)
  {
  digitalWrite(13, LOW);
  Serial.println("LOW");
  }
  
}

}
