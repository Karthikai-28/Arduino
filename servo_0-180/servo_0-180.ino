#include<Servo.h>
Servo myservo;
int pos;
int ldr=A0;
void setup() {
  Serial.begin(9600);
  myservo.attach(9);

}

void loop() {
pos=analogRead(ldr);
pos=map(pos,0,100,0,180);
myservo.write(pos);
delay(20);
Serial.println(ldr);
  
//  myservo.write(30);
//  delay(300);
//  myservo.write(60);
//  delay(300);  
//  myservo.write(90);
//  delay(300);
//  myservo.write(120);
//  delay(300);
//  myservo.write(150);
//  delay(300);
//  myservo.write(180);
//  delay(300);
//  myservo.write(0);
//  delay(300);
}
