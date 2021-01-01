#include<Servo.h>
Servo top_servo;

int lmotor1 = 5;
int lmotor2 = 4;
int rmotor1 = 10;
int rmotor2 = 9;
int duration, cm;
int trig = A1;
int echo = A0;

void setup() {
  pinMode(lmotor1, OUTPUT);
  pinMode(lmotor2, OUTPUT);
  pinMode(rmotor1, OUTPUT);
  pinMode(rmotor2, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, OUTPUT);
  top_servo.attach(11);

}

void loop() {
  top_servo.write(0,100);
  delay(600);
  ultrasonic_read();
  d1 = cm;
  top_servo.write(90,100);
  delay(600);
  ultrasonic_read();
  d2 = cm;
  top_servo.write(180,100);
  delay(600);
  ultrasonic_read();
  d3 = cm;

  if(d1>10&&d2>10&&d3>10)
   {
    if(d1>d2&&d1>d3)
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
 else
 {
  stp();
 }

}

void ultrasonic_read()
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
  digitalWrite(lmotor1,HIGH);
  digitalWrite(lmotor2,LOW);
  digitalWrite(rmotor1,HIGH);
  digitalWrite(rmotor2,LOW);
}

void backward()
{
  digitalWrite(lmotor1,LOW);
  digitalWrite(lmotor2,HIGH);
  digitalWrite(rmotor1,LOW);
  digitalWrite(rmotor2,HIGH);
}

void left()
{
  digitalWrite(lmotor1,LOW);
  digitalWrite(lmotor2,HIGH);
  digitalWrite(rmotor1,HIGH);
  digitalWrite(rmotor2,LOW);
}

void right()
{
  digitalWrite(lmotor1,HIGH);
  digitalWrite(lmotor2,LOW);
  digitalWrite(rmotor1,LOW);
  digitalWrite(rmotor2,HIGH);
}

void stp()
{
  digitalWrite(lmotor1,LOW);
  digitalWrite(lmotor2,LOW);
  digitalWrite(rmotor1,LOW);
  digitalWrite(rmotor2,LOW);
}

void stopleft()
{
  digitalWrite(lmotor1,LOW);
  digitalWrite(lmotor2,LOW);
  digitalWrite(rmotor1,HIGH);
  digitalWrite(rmotor2,LOW);
}

void stopright()
{
  digitalWrite(lmotor1,HIGH);
  digitalWrite(lmotor2,LOW);
  digitalWrite(rmotor1,LOW);
  digitalWrite(rmotor2,LOW);
}
