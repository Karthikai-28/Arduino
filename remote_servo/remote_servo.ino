#include <IRremote.h>      //must copy IRremote library to arduino libraries
#include <VarSpeedServo.h>

#define plus 0x107DF  //clockwise rotation button
#define minus 0x167D3  //counter clockwise rotation button


int RECV_PIN = A5;       //IR receiver pin
VarSpeedServo l2;
VarSpeedServo l1;
VarSpeedServo b1;
VarSpeedServo b2;
VarSpeedServo b3;
VarSpeedServo b4;

int val;                //rotation angle
bool cwRotation, ccwRotation;  //the states of rotation

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  l2.attach(5);     //servo pin
  l1.attach(2);
  b1.attach(3);
  b2.attach(4);
  b3.attach(7);
  b4.attach(8);
}

void loop() 
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value

    if (results.value == plus)
    {
      cwRotation = !cwRotation;    
      ccwRotation = false;         
    }

    if (results.value == minus)
    {
      ccwRotation = !ccwRotation;  
      cwRotation = false;            
    }
  }
  if (cwRotation && (val != 180))  {
    val++;                         
  }
  if (ccwRotation && (val != 0))  {
    val--;                         
  }
  b3.write(val);
  
  b1.write(val);
  
  b4.write(val);
  
  b2.write(val);

  l1.writeMicroseconds(1000);
  delay(20);          

}

