const byte encoder1 = 3;
const byte encoder2 = 2;
const float stepcount = 40;
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
void setup() {
Serial.begin(9600);
pinMode(DIR1,OUTPUT);
pinMode(DIR2,OUTPUT);
pinMode(PWM1,OUTPUT);
pinMode(PWM2,OUTPUT);
pinMode(encoder1, INPUT);
pinMode(encoder2, INPUT);
  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);

  Forward(1000, 100);

}


void loop() {


}
