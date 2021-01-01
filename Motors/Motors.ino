int lmotor1=5;
int lmotor2=6;
int rmotor1=10;
int rmotor2=11;

void setup()
{
  pinMode(lmotor1, OUTPUT);
  pinMode(lmotor2, OUTPUT);
  pinMode(rmotor1, OUTPUT);
  pinMode(rmotor2, OUTPUT);
}

void loop()
{
  digitalWrite(lmotor1, HIGH);
  digitalWrite(lmotor2, LOW);
  digitalWrite(rmotor1, HIGH);
  digitalWrite(rmotor2, LOW);
}

