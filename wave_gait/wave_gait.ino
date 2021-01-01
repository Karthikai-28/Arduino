#include<VarSpeedServo.h>

VarSpeedServo l1;
VarSpeedServo l2;
VarSpeedServo l3;
VarSpeedServo l4;

VarSpeedServo b1;
VarSpeedServo b2;
VarSpeedServo b3;
VarSpeedServo b4;

void setup()
{
  l1.attach(2);
  l2.attach(5);
  l3.attach(6);
  l4.attach(9);
  b1.attach(3);
  b2.attach(4);
  b3.attach(7);
  b4.attach(8);

  stand();
}

void loop()
{
  l1.write(90,100);
  delay (250);
  b1.write(140,100);
  delay (250);
  l1.write(60,100);
  delay (250);
  
  l4.write(90,100);
  delay (250);
  b4.write(40,100);
  delay (250);
  l4.write(60,100);
  delay (250);
  
  l2.write(90,100);
  delay (250);
  b2.write(140,100);
  delay (250);
  l2.write(60,100);
  delay (250);
  
  l3.write(90,100);
  delay (250);
  b3.write(40,100);
  delay (250);
  l3.write(60,100);
  delay (250);

  stand();
  delay (250);
}

void stand()
{
  b1.write(90,100);
  b2.write(90,100);
  b3.write(90,100);
  b4.write(90,100);

  l1.write(60,100);
  l2.write(60,100);
  l3.write(60,100);
  l4.write(60,100);
}

