const byte encoder1 = 3;
const byte encoder2 = 2;

const float stepcount = 20;

const float wheeldia = 100;

volatile int counter_A = 0;
volatile int counter_B = 0;

//Motor1

int DIR1 = 12;
int PWM1 = 10;

//Motor2

int DIR2 = 11;
int PWM2 = 9;

//ISR - Interrupt Service Routine (counting pulses with interrupts)

void setup()
{
  Serial.begin(9600);
  pinMode(DIR1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(encoder1, INPUT);
  pinMode(encoder2, INPUT);
  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);
}
void loop()
{
spinright(1340, 100);
delay(1000);
Forward(5000, 100);
delay(1000);
spinleft(1340, 100);
delay(1000);
circle();
delay(1000);
Stop(0,0);
delay(4000);
}


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

   digitalWrite(DIR1, HIGH);
   digitalWrite(DIR2, HIGH);
   Serial.println("Moving Forward");

   while(steps >= counter_A || steps >= counter_B){
    if (steps > counter_A){
      analogWrite(PWM1, mspeed);
    } else {
      analogWrite(PWM1, 0);
    }
    if (steps > counter_B){
      analogWrite(PWM2, mspeed);
    }else{
      analogWrite(PWM2, 0);
    }
   }

   analogWrite(PWM1, 0);
   analogWrite(PWM2, 0);
   counter_A = 0;
   counter_B = 0;
}

void Reverse(int steps, int mspeed)
{
  counter_A = 0;
  counter_B = 0;

   digitalWrite(DIR1, LOW);
   digitalWrite(DIR2, LOW);
   Serial.println("Moving Reverse");

   while (steps >= counter_A || steps >= counter_B) {

    
       if (steps > counter_A){
        analogWrite(PWM1, mspeed);
       } else {
        analogWrite(PWM1, 0);
      }
       if (steps > counter_B){
        analogWrite(PWM2, mspeed);
       }else{
        analogWrite(PWM2, 0);
       }
}

analogWrite(PWM1, 0);
analogWrite(PWM2, 0);
counter_A = 0;
counter_B = 0;
}

void spinright(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;

   digitalWrite(DIR1, LOW);
   digitalWrite(DIR2, HIGH);
   Serial.println("SPINING RIGHT");

      while (steps > counter_A && steps > counter_B) {
   
          if (steps > counter_A) {
          analogWrite(PWM1, mspeed);
          } else {
          analogWrite(PWM1, 0);
          }
          if (steps > counter_B) {
          analogWrite(PWM2, mspeed);
          } else {
          analogWrite(PWM2, 0);
          }
  }
  
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
  counter_A = 0;
  counter_B = 0;
} 

void spinleft(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;

   digitalWrite(DIR1, HIGH);
   digitalWrite(DIR2, LOW);
   Serial.println("SPINING LEFT");

      while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(PWM1, mspeed);
    } else {
    analogWrite(PWM1, 0);
    }
    if (steps > counter_B) {
    analogWrite(PWM2, mspeed);
    } else {
    analogWrite(PWM2, 0);
    }
  }
  
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
  counter_A = 0;
  counter_B = 0;
}

void Stop(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;

   digitalWrite(DIR1, LOW);
   digitalWrite(DIR2, LOW);
   Serial.println("ROBOT IN STATIC POSITION");

      while (steps > counter_A || steps > counter_B) {
   
    if (steps > counter_A) {
    analogWrite(PWM1, mspeed);
    } else {
    analogWrite(PWM1, 0);
    }
    if (steps > counter_B) {
    analogWrite(PWM2, mspeed);
    } else {
    analogWrite(PWM2, 0);
    }
  }
  
  analogWrite(PWM1, 0);
  analogWrite(PWM2, 0);
  counter_A = 0;
  counter_B = 0;
}


void circle(){
  analogWrite(PWM1, 120);
  analogWrite(PWM2, 80);

  digitalWrite(DIR1, HIGH);
  digitalWrite(DIR2, HIGH);
  

  delay(10000);
  
}
