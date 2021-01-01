int lmotor1=5;
int lmotor2=6;
int rmotor1=10;
int rmotor2=11;
int sensor=2;
int IRsensor=0;

void setup()
{
  pinMode(sensor,INPUT);
  pinMode(lmotor1, OUTPUT);
  pinMode(lmotor2, OUTPUT);
  pinMode(rmotor1, OUTPUT);
  pinMode(rmotor2, OUTPUT);
}

void loop()
{
  IRsensor=digitalRead(sensor);
  if(IRsensor==HIGH){
  digitalWrite(lmotor1, HIGH);
  digitalWrite(lmotor2, LOW);
  digitalWrite(rmotor1, LOW);
  digitalWrite(rmotor2, LOW);
}
else{
  digitalWrite(lmotor1, LOW);
  digitalWrite(lmotor2, HIGH);
  digitalWrite(rmotor1, HIGH);
  digitalWrite(rmotor2, LOW);
  
}
}
