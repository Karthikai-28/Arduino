const byte encoder1 = 2;
const byte encoder2 = 3;
const byte encoder3 = 4;
const byte encoder4 = 5;

const float stepcount =20 ;

const float wheeldia = 60;

volatile int counter_A = 0;
volatile int counter_B = 0;
volatile int counter_C = 0;
volatile int counter_D = 0;

//Motor1

int lm1 = 6;
int mbr1 = 7;
int pwm1 = 10;

//Motor2

int rm1 = 8;
int mbr2 = 9;
int pwm2 = 11;

//ISR - Interrupt Service Routine (counting pulses with interrupts)


void ISR_countA()
{
  counter_A++;
}

void ISR_countB()
{
  counter_B++;
}
void ISR_countC()
{
  counter_C++;
}

void ISR_countD()
{
  counter_D++;
}

int CMtoSteps(float cm){
  Serial.begin(9600);
  int result;
  float circumference = (wheeldia * 3.14) / 10;
  Serial.print("Circumference is...");
  Serial.println(circumference);
  float cm_step = circumference/stepcount;
  Serial.print("cm_step is...");
  Serial.println(cm_step);
  float f_result = cm/cm_step;
  Serial.print(f_result);
  result = (int) f_result;
  Serial.print(result);



  return result;
}

//void angle(float degree){
//  float precision = 360/0.94;
//  float Angle = 0.235*precision;
//  Serial.print("Angle is...");
//  Serial.println(Angle);
//}

void Forward(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;
  counter_C = 0;
  counter_D = 0;
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, HIGH);
   Serial.println("Moving Forward");

   while(steps > counter_A || steps > counter_B || steps > counter_C || steps > counter_D){
    if (steps > counter_A){
      analogWrite(pwm1, mspeed);
    } else {
      analogWrite(pwm1, 0);
    }
    if (steps > counter_B){
      analogWrite(pwm1, mspeed);
    }else{
      analogWrite(pwm1, 0);
    }
   
   if (steps > counter_C){
      analogWrite(pwm2, mspeed);
    }else{
      analogWrite(pwm2, 0);
    }
   
   if (steps > counter_D){
      analogWrite(pwm2, mspeed);
    }else{
      analogWrite(pwm2, 0);
    }
   }
   analogWrite(pwm1, 0);
   analogWrite(pwm2, 0);
   counter_A = 0;
   counter_B = 0;
   counter_C = 0;
   counter_D = 0;
}


void Reverse(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;
  counter_C = 0;
  counter_D = 0;

   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, LOW);
   Serial.println("Moving Reverse");

   while (steps > counter_A || steps > counter_B || steps > counter_C || steps > counter_D) {


   if (steps > counter_A){
    analogWrite(pwm1, mspeed);
   } else {
    analogWrite(pwm1, 0);
  }
   if (steps > counter_B){
    analogWrite(pwm1, mspeed);
   }else{
    analogWrite(pwm1, 0);
   }
   if (steps > counter_C){
    analogWrite(pwm2, mspeed);
   }else{
    analogWrite(pwm2, 0);
   }
   if (steps > counter_D){
    analogWrite(pwm2, mspeed);
   }else{
    analogWrite(pwm2, 0);
   }
}

analogWrite(pwm1, 0);
analogWrite(pwm2, 0);
  counter_A = 0;
  counter_B = 0;
  counter_C = 0;
  counter_D = 0;
}

void spinright(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;
  counter_C = 0;
  counter_D = 0;

   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, LOW);
   Serial.println("SPIN RIGHT");

      while (steps > counter_A || steps > counter_B || steps > counter_C || steps > counter_D) {
   
    if (steps > counter_A) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
    if (steps > counter_B) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
    if (steps > counter_C) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
    if (steps > counter_D) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
   }
   analogWrite(pwm1, 0);
   analogWrite(pwm2, 0);
  counter_A = 0;
  counter_B = 0;
  counter_C = 0;
  counter_D = 0;
}

//void turnright()
//   {
//   digitalWrite(mbr1, LOW);
//   digitalWrite(mbr2, LOW);
//   digitalWrite(pwm1, 120);
//   digitalWrite(pwm2, 60);
//   digitalWrite(lm1, LOW);
//   digitalWrite(rm1, HIGH);
//   Serial.println("RIGHT");
//   }

void spinleft(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;
  counter_C = 0;
  counter_D = 0;

   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, HIGH);
   Serial.println("SPIN LEFT");

      while (steps > counter_A || steps > counter_B || steps > counter_C || steps > counter_D) {
   
    if (steps > counter_A) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
    if (steps > counter_B) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
     if (steps > counter_C) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
    if (steps > counter_D) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
  }
  
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  counter_A = 0;
  counter_B = 0;
  counter_C = 0;
  counter_D = 0;
}

//void turnleft(int steps, int mspeed)
//{
//   counter_A = 0;
//   counter_B = 0;
//
//   digitalWrite(mbr1, LOW);
//   digitalWrite(mbr2, HIGH);
//   //digitalWrite(pwm1, HIGH);
//   //digitalWrite(pwm2, HIGH);
//   digitalWrite(lm1, HIGH);
//   digitalWrite(rm1, LOW);
//   Serial.println("TURN LEFT");
//
//      while (steps > counter_A || steps > counter_B) {
//   
//    if (steps > counter_A) {
//    analogWrite(pwm1, mspeed);
//    } else {
//    analogWrite(pwm1, 0);
//    }
//    if (steps > counter_B) {
//    analogWrite(pwm2, mspeed);
//    } else {
//    analogWrite(pwm2, 0);
//    }
//  }
//  
//  analogWrite(pwm1, 0);
//  analogWrite(pwm2, 0);
//  counter_A = 0;
//  counter_B = 0;
//}

void setup()
{
Serial.begin(9600);
pinMode(lm1,OUTPUT);
pinMode(rm1,OUTPUT);
pinMode(mbr1,OUTPUT);
pinMode(mbr2,OUTPUT);
pinMode(pwm1,OUTPUT);
pinMode(pwm2,OUTPUT);
pinMode(encoder1, INPUT);
pinMode(encoder2, INPUT);
pinMode(encoder3, INPUT);
pinMode(encoder4, INPUT);
  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder3), ISR_countC, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder4), ISR_countD, RISING);
  


  


}
void loop()
{

  Forward(70, 100);
  delay(1000);
  
  Reverse(70, 100);
  delay(1000);
  
  spinleft(50, 100);
  delay(1000);
  
  spinright(50,100);
  delay(1000);
}
