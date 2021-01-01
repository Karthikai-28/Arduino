#include <CytronMotorDriver.h>

const byte encoder1 = 3;
const byte encoder2 = 2;

const float stepcount = 20;

const float wheeldia = 100;

volatile int counter_A = 0;
volatile int counter_B = 0;

CytronMD motor1(PWM_PWM, 3, 9);
CytronMD motor2(PWM_PWM, 10, 11);

//ISR - Interrupt Service Routine (counting pulses with interrupts)


void ISR_countA()
{
  counter_A++;
}

void ISR_countB()
{
  counter_B++;
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



void Forward(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;

   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, HIGH);
   Serial.println("Moving Forward");

   while(steps >= counter_A || steps >= counter_B){
    if (steps > counter_A){
      analogWrite(pwm1, mspeed);
    } else {
      analogWrite(pwm1, 0);
    }
    if (steps > counter_B){
      analogWrite(pwm2, mspeed);
    }else{
      analogWrite(pwm2, 0);
    }
   }

   analogWrite(pwm1, 0);
   analogWrite(pwm2, 0);
   counter_A = 0;
   counter_B = 0;
}


void Reverse(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;


   digitalWrite(lm1, LOW);
   digitalWrite(rm1, LOW);
   Serial.println("Moving Reverse");

   while (steps >= counter_A || steps >= counter_B) {


   if (steps > counter_A){
    analogWrite(pwm1, mspeed);
   } else {
    analogWrite(pwm1, 0);
  }
   if (steps > counter_B){
    analogWrite(pwm2, mspeed);
   }else{
    analogWrite(pwm2, 0);
   }
}

analogWrite(pwm1, 0);
analogWrite(pwm2, 0);
counter_A = 0;
counter_B = 0;
}

void spinright(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;

   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, LOW);
   Serial.println("SPINING RIGHT");

      while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
    if (steps > counter_B) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
  }
  
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  counter_A = 0;
  counter_B = 0;
}

void spinleft(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;


   digitalWrite(lm1, LOW);
   digitalWrite(rm1, HIGH);
   Serial.println("SPINING LEFT");

      while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
    if (steps > counter_B) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
  }
  
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  counter_A = 0;
  counter_B = 0;
}

void turnleft(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;


   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, LOW);
   Serial.println("TURNING LEFT");

      while (steps > counter_A || steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
    if (steps > counter_B) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
  }
  
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  counter_A = 0;
  counter_B = 0;
}

void Stop(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;

   digitalWrite(lm1, LOW);
   digitalWrite(rm1, LOW);
   Serial.println("ROBOT IN STATIC POSITION");

      while (steps > counter_A || steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
    if (steps > counter_B) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
  }
  
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  counter_A = 0;
  counter_B = 0;
}

void turnright(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;


   digitalWrite(lm1, LOW);
   digitalWrite(rm1, HIGH);
   Serial.println("TURNING RIGHT");

      while (steps > counter_A || steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(pwm1, mspeed);
    } else {
    analogWrite(pwm1, 0);
    }
    if (steps > counter_B) {
    analogWrite(pwm2, mspeed);
    } else {
    analogWrite(pwm2, 0);
    }
  }
  
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  counter_A = 0;
  counter_B = 0;
}

void setup()
{
Serial.begin(9600);
pinMode(lm1,OUTPUT);
pinMode(rm1,OUTPUT);
//pinMode(mbr1,OUTPUT);
//pinMode(mbr2,OUTPUT);
pinMode(pwm1,OUTPUT);
pinMode(pwm2,OUTPUT);
pinMode(encoder1, INPUT);
pinMode(encoder2, INPUT);
  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);

  delay(3000);
}
void loop()
{
//Maze movement

Forward(5100, 100);
delay(1000);

Stop(0,0);
delay(1000);

spinleft(1340, 100);
delay(1000);

Forward(3100, 100);
delay(1000);

Stop(0,0);
delay(1000);

spinleft(1340, 100);
delay(1000);

Stop(0,0);
delay(1000);

Forward(5100, 100);
delay(1000);

spinright(1340, 100);
delay(1000);
}
