const byte encoder1 = 3;
const byte encoder2 = 2;

const float stepcount = 20;

const float wheeldia = 60;

volatile int counter_A = 0;
volatile int counter_B = 0;

//Motor1

int lm1 = 5;
int mbr1 = 7;
int pwm1 = 10;

//Motor2

int rm1 = 6;
int mbr2 = 4;
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
   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, LOW);
   Serial.println("Moving Forward");

   while(steps > counter_A || steps > counter_B){
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

   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, HIGH);
   Serial.println("Moving Reverse");

   while (steps > counter_A || steps > counter_B) {


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

   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, LOW);
   digitalWrite(rm1, HIGH);
   Serial.println("SPIN RIGHT");
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
    
  // Stop when done
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}

void spinleft(int steps, int mspeed)
{
   counter_A = 0;
   counter_B = 0;

   digitalWrite(mbr1, LOW);
   digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(lm1, HIGH);
   digitalWrite(rm1, LOW);
   Serial.println("SPIN LEFT");

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
    
  // Stop when done
  analogWrite(pwm1, 0);
  analogWrite(pwm2, 0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}

void setup()
{

pinMode(lm1,OUTPUT);
pinMode(rm1,OUTPUT);
pinMode(mbr1,OUTPUT);
pinMode(mbr2,OUTPUT);
pinMode(pwm1,OUTPUT);
pinMode(pwm2,OUTPUT);
  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);

  Forward(CMtoSteps(50), 180);  
  delay(1000); 
  Reverse(10, 150);  
  delay(1000); 
  Forward(10, 150); 
  delay(1000);  
  Reverse(CMtoSteps(25.4), 200);   
  delay(1000);  
  spinright(20, 150);  
  delay(1000); 
  spinleft(60, 155);  
  delay(1000);  
  Forward(1, 180);  
  
  
} 
void loop()
{
  
}
