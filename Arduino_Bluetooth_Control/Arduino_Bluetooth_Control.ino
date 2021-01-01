#include <SoftwareSerial.h>

SoftwareSerial BT(0,1); //TX, RX respetively
String readdata;

//Motor1

int lm1 = 5;
int mbr1 = 7;
int pwm1 = 10;

//Motor2

int rm1 = 6;
int mbr2 = 4;
int pwm2 = 11;

void setup() {
 BT.begin(9600);
 Serial.begin(9600);
  pinMode(5, OUTPUT); 
  pinMode(6, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 

}

void loop() {
  while (BT.available()){ 
  delay(10);
  char c = BT.read();
  readdata += c; 
  } 
  if (readdata.length() > 0) {
    Serial.println(readdata); 

  if(readdata == "1") 
  {
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   analogWrite(pwm1, 30);
   analogWrite(pwm2, 70);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, HIGH);
   Serial.println("Moving Forward");
   delay (100);
  }
 

  else if(readdata == "2")
  {
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   analogWrite(pwm1, 30);
   analogWrite(pwm2, 70);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, LOW);
   Serial.println("Moving Reverse");
   delay (100);
  }

  else if (readdata == "3")
  {
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   analogWrite(pwm1, 30);
   analogWrite(pwm2, 70);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, LOW);
   Serial.println("SPIN RIGHT");
   delay (100);
   
  }

 else if ( readdata == "4")
 {
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   analogWrite(pwm1, 30);
   analogWrite(pwm2, 70);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, HIGH);
   Serial.println("SPIN LEFT");
   delay (100);
 }
 else if (readdata == "5")
 {
   digitalWrite(mbr1, HIGH);
   digitalWrite(mbr2, HIGH);
  analogWrite(pwm1, 0);
   analogWrite(pwm2, 0);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, LOW);
   Serial.println("SPIN LEFT");
   delay (100);
 }

  


readdata="";}} //Reset the variable
