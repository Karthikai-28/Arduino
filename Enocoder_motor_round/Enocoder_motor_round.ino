const byte encoder1 = 3;
const byte encoder2 = 2;

const float stepcount = 40;

const float wheeldia = 100;

volatile int counter_A = 0;
volatile int counter_B = 0;

//Motor1

int lm1 = 4;
//int mbr1 = 7;
int pwm1 = 5;

//Motor2

int rm1 = 7;
//int mbr2 = 9;
int pwm2 = 6;

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

//1 STEP = 0.785 CM

  return result;
}


void Forward(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;

   digitalWrite(lm1, LOW);
   digitalWrite(rm1, LOW);
//   analogWrite(lm1, 125);
//   analogWrite(rm1, 125);
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

//   analogWrite(lm1, -125);
//   analogWrite(rm1, -125);
   digitalWrite(lm1, HIGH);
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

   digitalWrite(lm1, LOW);
   digitalWrite(rm1, HIGH);
//   analogWrite(lm1, 125);
//   analogWrite(rm1, -125);
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
//   analogWrite(lm1, -125);
//   analogWrite(rm1, 125);
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

//   digitalWrite(mbr1, LOW);
//   digitalWrite(mbr2, HIGH);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
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

//   digitalWrite(mbr1, HIGH);
//   digitalWrite(mbr2, HIGH);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
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

//   digitalWrite(mbr1, HIGH);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
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

 // delay(3000);


Forward(10000, 100);
delay(1000);
Stop(0,0);
delay(1000);
Reverse(10000, 100);
delay(1000);
Stop(0,0);
delay(1000);
spinright(10000, 100);
delay(1000);
Stop(0,0);
delay(1000);
spinleft(10000, 100);
delay(1000);
Stop(0,0);
delay(1000);



}
void loop()
{


}
