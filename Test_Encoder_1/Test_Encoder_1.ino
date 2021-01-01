//Pin Allocation
const int encoder_1 = 2;
const int encoder_2 = 3;
const int PWM_1 = 10;
const int DIR_1 = 12;
const int PWM_2 = 9;
const int DIR_2 = 11;

//Input variables

const int motor_power = 20;                            //Speed for the motor
const int motor_offset = 22;                           //Difference When driving straight
const int wheel_diameter = 100;                        //in mm
const float wheel_circumference = PI*wheel_diameter;   //Wheel circumference 314mm
const int counts_per_revolution = 9840;                // 60 * 164 = 9840

volatile int counter_A = 0;
volatile int counter_B = 0;

float motor_Speed;

void setup()
{
  Serial.begin(9600);

  pinMode(encoder_1, INPUT_PULLUP);
  pinMode(encoder_2, INPUT_PULLUP);
  pinMode(PWM_1, OUTPUT);
  pinMode(DIR_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(DIR_2, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(encoder_1), counter_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder_2), counter_2, CHANGE);

  delay(100);

  Forward(40,100);
  delay(1000);
  Reverse(40,100);
  
}

void loop(){
  
}

void Forward(int distance, int power)
{
  unsigned long number_ticks_1;
  unsigned long number_ticks_2;

  int power_1 = motor_power;
  int power_2 = motor_power;

  unsigned long diff_1;
  unsigned long diff_2;

  counter_A = 0;
  counter_B = 0;

  unsigned long encoder_1_previous = counter_A;
  unsigned long encoder_2_previous = counter_B;

  float number_revolutions = (distance * 10) / wheel_circumference;
  unsigned long target_count = number_revolutions * counts_per_revolution;

  motor_Speed = (power/255)*100;


  Serial.print("Driving forward for ");
  Serial.print(distance);
  Serial.print(" cm ( ");
  Serial.print(target_count);
  Serial.print(" ticks) at ");
  Serial.print(motor_Speed);
  Serial.println("% Motor Speed ");

  
   digitalWrite(DIR_1, HIGH);
   digitalWrite(DIR_2, HIGH);
   Serial.println("Acceleration");

   while((target_count >= counter_A) && (target_count >= counter_B)){

    number_ticks_1 = counter_A;
    number_ticks_2 = counter_B;

    Serial.print(number_ticks_1);
    Serial.print("\t");
    Serial.println(number_ticks_2);

    diff_1 = number_ticks_1 - encoder_1_previous;
    diff_2 = number_ticks_2 - encoder_2_previous;

    encoder_1_previous = number_ticks_1;
    encoder_2_previous = number_ticks_2;
    
    if (target_count > counter_A){
      analogWrite(PWM_1, power);
    } else {
      analogWrite(PWM_1, 0);
    }
    if (target_count > counter_B){
      analogWrite(PWM_2, power);
    }else{
      analogWrite(PWM_2, 0);
    }
        //If left is faster, slow it down and speed up right
    if (diff_1 > diff_2)
    {
      power_1 -= motor_offset;
      power_2 -= motor_offset;
    }

    //If right is faster, slow it down and speed up left
    if (diff_1 < diff_2)
    {
      power_1 -= motor_offset;
      power_2 -= motor_offset;
    }

    delay(20);
   }

   analogWrite(PWM_1, 0);
   analogWrite(PWM_2, 0);
   counter_A = 0;
   counter_B = 0;
}

void Reverse(int distance, int power)
{
  unsigned long number_ticks_1;
  unsigned long number_ticks_2;

  int power_1 = motor_power;
  int power_2 = motor_power;

  unsigned long diff_1;
  unsigned long diff_2;

  counter_A = 0;
  counter_B = 0;

  unsigned long encoder_1_previous = counter_A;
  unsigned long encoder_2_previous = counter_B;

  float number_revolutions = (distance * 10) / wheel_circumference;
  unsigned long target_count = number_revolutions * counts_per_revolution;

  motor_Speed = (power/255)*100;


  Serial.print("Driving Reverse for ");
  Serial.print(distance);
  Serial.print(" cm ( ");
  Serial.print(target_count);
  Serial.print(" ticks) at ");
  Serial.print(motor_Speed);
  Serial.println("% Motor Speed ");

  
   digitalWrite(DIR_1, LOW);
   digitalWrite(DIR_2, LOW);
   Serial.println("Deceleration");

   while((target_count >= counter_A) && (target_count >= counter_B)){

    number_ticks_1 = counter_A;
    number_ticks_2 = counter_B;

    Serial.print(number_ticks_1);
    Serial.print("\t");
    Serial.println(number_ticks_2);

    diff_1 = number_ticks_1 - encoder_1_previous;
    diff_2 = number_ticks_2 - encoder_2_previous;

    encoder_1_previous = number_ticks_1;
    encoder_2_previous = number_ticks_2;
    
    if (target_count > counter_A){
      analogWrite(PWM_1, power);
    } else {
      analogWrite(PWM_1, 0);
    }
    if (target_count > counter_B){
      analogWrite(PWM_2, power);
    }else{
      analogWrite(PWM_2, 0);
    }
        //If left is faster, slow it down and speed up right
    if (diff_1 > diff_2)
    {
      power_1 -= motor_offset;
      power_2 -= motor_offset;
    }

    //If right is faster, slow it down and speed up left
    if (diff_1 < diff_2)
    {
      power_1 -= motor_offset;
      power_2 -= motor_offset;
    }

    delay(20);
   }

   analogWrite(PWM_1, 0);
   analogWrite(PWM_2, 0);
   counter_A = 0;
   counter_B = 0;
}

void brake()
{
  digitalWrite(PWM_1, LOW);
  digitalWrite(PWM_2, LOW);
  digitalWrite(DIR_1, LOW);
  digitalWrite(DIR_2, LOW);
}

void counter_1()
{
  counter_A++;
}

void counter_2()
{
  counter_B++;
}
