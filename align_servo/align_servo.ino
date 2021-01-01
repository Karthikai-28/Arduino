#include<VarSpeedServo.h>


VarSpeedServo b3;


void setup()
{
  b3.attach(7);
  

 

}
void loop()
{
  b3.write(0,100);
  delay(1000);
  b3.write(180,100);
  delay(1000);
}
