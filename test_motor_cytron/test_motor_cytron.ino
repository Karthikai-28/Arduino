int lm1 = A5;
int pmw1=11;


void setup() {
pinMode(lm1, OUTPUT);
pinMode(pmw1, OUTPUT);


}

void loop() {
//  digitalWrite(lm1, HIGH);
//  digitalWrite(pmw1, HIGH);
//
//  delay(1000);
//
//  digitalWrite(lm1, LOW);
//  digitalWrite(pmw1, HIGH);
//
//  delay(1000);
//
//  digitalWrite(lm1, HIGH);
//  digitalWrite(pmw1, LOW);
//
//  delay(1000);
//
//  digitalWrite(lm1, LOW);
//  digitalWrite(pmw1, LOW);
//
//  delay(1000);
Reverse();
}

void Reverse()
{


   
   analogWrite(lm1, -255);   //RIGHT MOTOR
   analogWrite(pmw1, -125);
   
   Serial.println("Moving Reverse");
//
//   while (steps >= counter_A || steps >= counter_B) {
//
//    
//       if (steps > counter_A){
//        analogWrite(pwm1, mspeed);
//       } else {
//        analogWrite(pwm1, 0);
//      }
//       if (steps > counter_B){
//        analogWrite(pwm2, mspeed);
//       }else{
//        analogWrite(pwm2, 0);
//       }
//}
//
//analogWrite(pwm1, 0);
//analogWrite(pwm2, 0);
//counter_A = 0;
//counter_B = 0;
}
