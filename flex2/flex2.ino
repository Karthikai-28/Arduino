#include<Servo.h>
Servo servo1;
Servo servo2;

const int flexPin1=A0;
const int flexPin2=A1;

void setup()
{
  servo1.attach(3);
  servo2.attach(5);
}

void loop()
{
  int flexPosition1;
  int servoPosition1;
  int flexPosition2;
  int servoPosition2;

  flexPosition1 = analogRead(flexPin1);
  flexPosition2 = analogRead(flexPin2);

  servoPosition1 = map(flexPosition1, 600, 900, 0, 180);
  servoPosition1 = constrain(servoPosition1, 0, 180);
  servoPosition2 = map(flexPosition2, 600, 900, 0, 180);
  servoPosition2 = constrain(servoPosition2, 0, 180);

  servo1.write(servoPosition1);
  servo2.write(servoPosition2);

}



