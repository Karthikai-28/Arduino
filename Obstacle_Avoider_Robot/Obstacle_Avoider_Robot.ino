#include<VarSpeedServo.h>
VarSpeedServo topservo;

int lmotora = 10;
int lmotorb = 9;
int rmotora = 7;
int rmotorb = 6;
int duration, cm;
int trig = A1;
int echo = A0;
int d1, d2, d3;
void setup() {
  pinMode(lmotora, OUTPUT);
  pinMode(lmotorb, OUTPUT);
  pinMode(rmotora, OUTPUT);
  pinMode(rmotorb, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, OUTPUT);
  topservo.attach(11);

}

void ultrasonic()
{
    digitalWrite(trig, LOW);
    delay(2);
    digitalWrite(trig, HIGH);
    delay(10);
    digitalWrite(trig, LOW);
    delay(2);
    duration = pulseIn(echo, HIGH);

    cm = (duration/29/2);
    delay(100);
}


void forward()
{
  digitalWrite(lmotora,HIGH);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotora,HIGH);
  digitalWrite(rmotorb,LOW);
}

void backward()
{
  digitalWrite(lmotora,LOW);
  digitalWrite(lmotorb,HIGH);
  digitalWrite(rmotora,LOW);
  digitalWrite(rmotorb,HIGH);
}

void left()
{
  digitalWrite(lmotora,LOW);
  digitalWrite(lmotorb,HIGH);
  digitalWrite(rmotora,HIGH);
  digitalWrite(rmotorb,LOW);
}

void right()
{
  digitalWrite(lmotora,HIGH);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotora,LOW);
  digitalWrite(rmotorb,HIGH);
}

void stp()
{
  digitalWrite(lmotora,LOW);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotora,LOW);
  digitalWrite(rmotorb,LOW);
}

void stopleft()
{
  digitalWrite(lmotora,LOW);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotora,HIGH);
  digitalWrite(rmotorb,LOW);
}

void stopright()
{
  digitalWrite(lmotora,HIGH);
  digitalWrite(lmotorb,LOW);
  digitalWrite(rmotora,LOW);
  digitalWrite(rmotorb,LOW);
}
void loop() {
  topservo.write(0,100);
  delay(600);
  ultrasonic();
  d1 = cm;
  topservo.write(90,100);
  delay(600);
  ultrasonic();
  d2 = cm;
  topservo.write(180,100);
  delay(600);
  ultrasonic();
  d3 = cm;

 if(d1>10&&d2>10&&d3>10)
 {
    if(d1>d2&&d1>d3)
    {
      left();
    }
    else if (d2>d3&&d2>d1)
    {
      forward();
    }
    else
    {
      right();
    }
 }
 else
  {
    stp();
  }
 }
 
