int lm1 = 7;
int rm1 = 6;
int mbr1 = 5;
int mbr2 = 4;
int pwm1 = 10;
int pwm2 = 11;
char val, w, x, z, d, a;

void setup() {
Serial.begin(9600);
pinMode(lm1,OUTPUT);
pinMode(rm1,OUTPUT);
pinMode(mbr1,OUTPUT);
pinMode(mbr2,OUTPUT);
pinMode(pwm1,OUTPUT);
pinMode(pwm2,OUTPUT);
}

void loop() {
  if (Serial.available())
  {
   val = Serial.read();
   if(val == 'w')
   {
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   digitalWrite(pwm1, HIGH);
   digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, LOW);
   Serial.println("Moving Forward");
   }
   else if (val =='x')
   {
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   analogWrite(pwm1, 120);
   analogWrite(pwm2, 255);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, HIGH);
   Serial.println("Moving Reverse");
   }
   else if (val =='z')
   {
   digitalWrite(mbr1, HIGH);
   digitalWrite(mbr2, HIGH);
   digitalWrite(pwm1, HIGH);
   digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, LOW);
   Serial.println("STOP");
   }
      else if (val =='d')
   {
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   digitalWrite(pwm1, 120);
   digitalWrite(pwm2, 60);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, LOW);
   Serial.println("LEFT");
   }
      else if (val =='a')
   {
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   digitalWrite(pwm1, 120);
   digitalWrite(pwm2, 60);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, HIGH);
   Serial.println("RIGHT");
   }
  }
}
