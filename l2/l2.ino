#include<VarSpeedServo.h>

VarSpeedServo l2;

void setup()
{
  l2.attach(5);
}

void loop()
{
  delay(3000);
  l2.write(0,30);
  delay(3000);
  l2.write(180,30);
}

