int IRsensor = 6;
int bulb = 13;
int Obstacle = HIGH;
void setup()
{
  Serial.begin(9600);
  pinMode(IRsensor, INPUT);
  pinMode(bulb, OUTPUT);
}

void loop()
{
  Obstacle=digitalRead(IRsensor);

  if (Obstacle == LOW)
  {Serial.println("STOPPED");
  digitalWrite(bulb, HIGH);
  }
  else
  {
    Serial.println("RUNNING");
    digitalWrite(bulb, LOW);
    
  }
  delay(300);
}

