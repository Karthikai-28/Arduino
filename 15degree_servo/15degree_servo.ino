#include<Servo.h>
int servoPin = 9;
Servo servo;
int angle = 0;

void setup () {
servo.attach(servoPin);  

Serial.begin(115200);
while (!Serial);
Serial.println("Enter angle(int): 0-180");
}

void loop() {
  if (Serial.available()>0){
    angle = Serial.parseInt();
    Serial.println(angle);

    servo.write (angle);
    delay(1000);
  }
}
//#include <Servo.h> 
//
//Servo servo;
//
//int pos = 0;
//
//void setup() 
//{ 
//  servo.attach(9);
//   // set servo to mid-point
//} 
//
//void loop() {
//  for (pos =0; pos <= 75; pos+=1)
//
// {
//  servo.write(pos);
//  delay(1000);
// }
// for (pos =75; pos >= 0; pos-=1)
// {
// servo.write(pos);
// delay(1000);
//}
//  } 
//#include<Servo.h>
//Servo s1;
//int pos =0;
//void setup()
//{
// s1.attach(10);
//  s1.write(0);
//  delay (2000);
//  s1.write(15);
//  delay (2000);
//  s1.write(0);
//  delay (2000);
//}
//
//void loop()
//{
//
//}
