#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;   


const int flexPin1 = A0; 
const int flexPin2 = A1;
const int flexPin3 = A2;
const int flexPin4 = A3;
const int flexPin5 = A4;

void setup() 
{ 

  Serial.begin(9600); //Set serial baud rate to 9600 bps

  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo5.attach(10);  
  
} 


void loop() 
{ 
  int flexPosition1;   
  int servoPosition1; 
  int flexPosition2;   
  int servoPosition2; 
  int flexPosition3;   
  int servoPosition3;
  int flexPosition4;   
  int servoPosition4; 
  int flexPosition5;   
  int servoPosition5;   

  // Read the position of the flex sensor (0 to 1023):

  flexPosition1 = analogRead(flexPin1);
  flexPosition2 = analogRead(flexPin2);
  flexPosition3 = analogRead(flexPin3);
  flexPosition4 = analogRead(flexPin4);
  flexPosition5 = analogRead(flexPin5);


  servoPosition1 = map(flexPosition1, 600, 650, 0, 180);
  servoPosition1 = constrain(servoPosition1, 0, 180);
  servoPosition2 = map(flexPosition2, 600, 650, 0, 180);
  servoPosition2 = constrain(servoPosition2, 0, 180);
  servoPosition3 = map(flexPosition3, 600, 650, 0, 180);
  servoPosition3 = constrain(servoPosition3, 0, 180);
  servoPosition4 = map(flexPosition4, 600, 650, 0, 180);
  servoPosition4 = constrain(servoPosition4, 0, 180);
  servoPosition5 = map(flexPosition5, 600, 650, 0, 180);
  servoPosition5 = constrain(servoPosition5, 0, 180);

  // Now we'll command the servo to move to that position:

  servo1.write(servoPosition1);
  servo2.write(servoPosition2);
  servo3.write(servoPosition3);
  servo4.write(servoPosition4);
  servo5.write(servoPosition5);


  Serial.print("sensor1: ");
  Serial.print(flexPosition1);
  Serial.print("  servo1: ");
  Serial.println(servoPosition1);
  
  Serial.print("sensor2: ");
  Serial.print(flexPosition2);
  Serial.print("  servo2: ");
  Serial.println(servoPosition2);
  
  Serial.print("sensor3: ");
  Serial.print(flexPosition3);
  Serial.print("  servo3: ");
  Serial.println(servoPosition3);
  
  Serial.print("sensor4: ");
  Serial.print(flexPosition4);
  Serial.print("  servo4: ");
  Serial.println(servoPosition4);
  
  Serial.print("sensor5: ");
  Serial.print(flexPosition5);
  Serial.print("  servo5: ");
  Serial.println(servoPosition5);
} 

