const byte encoder1 = 3;
int pwm1=10;
int dir=12;
int brk=8;

volatile long encoderValue = 0;

int interval = 1000;
long previousMillis = 0;
long currentMillis = 0;

int rpm = 0;
boolean measureRpm = false;
int motorPwm = 0;
volatile int counter_A = 0;


void ISR_countA()
{
  counter_A++;
}

void Forward(int steps, int mspeed)
{
  counter_A = 0;
  //counter_B = 0;
   digitalWrite(brk, LOW);
   //digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(dir, HIGH);
 //  digitalWrite(rm1, HIGH);
   Serial.println("Moving Forward");

   while(steps > counter_A ){
    if (steps > counter_A){
      analogWrite(pwm1, mspeed);
    } else {
      analogWrite(pwm1, 0);
    }
//    if (steps > counter_B){
//      analogWrite(pwm2, mspeed);
//    }else{
//      analogWrite(pwm2, 0);
//    }
   }

   analogWrite(pwm1, 0);
  // analogWrite(pwm2, 0);
   counter_A = 0;
   //counter_B = 0;
}

void Reverse(int steps, int mspeed)
{
  counter_A = 0;
  //counter_B = 0;
   digitalWrite(brk, LOW);
   //digitalWrite(mbr2, LOW);
   //digitalWrite(pwm1, HIGH);
   //digitalWrite(pwm2, HIGH);
   digitalWrite(dir, LOW);
 //  digitalWrite(rm1, HIGH);
   Serial.println("Moving Forward");

   while(steps > counter_A ){
    if (steps > counter_A){
      analogWrite(pwm1, mspeed);
    } else {
      analogWrite(pwm1, 0);
    }
//    if (steps > counter_B){
//      analogWrite(pwm2, mspeed);
//    }else{
//      analogWrite(pwm2, 0);
//    }
   }

   analogWrite(pwm1, 0);
  // analogWrite(pwm2, 0);
   counter_A = 0;
   //counter_B = 0;
}

void setup()
{
  Serial.begin(9600);
  pinMode(encoder1, INPUT_PULLUP);
  pinMode(pwm1, OUTPUT);
  pinMode(dir, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(encoder1), ISR_countA, RISING);

  //Forward(100, 255);
  Reverse(100, 255);
}

void loop()
{
  
}
