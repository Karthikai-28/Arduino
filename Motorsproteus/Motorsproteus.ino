int motora=10;
int motorb=9;
int motorc=5;
int motord=4;

void setup() 
{
 pinMode(motora,OUTPUT);
pinMode(motorb,OUTPUT);
pinMode(motorc,OUTPUT);
pinMode(motord,OUTPUT);

 digitalWrite(motora,HIGH);
  digitalWrite(motorb,LOW);
   digitalWrite(motorc,HIGH);
    digitalWrite(motord,LOW);
}

void loop()
{}
