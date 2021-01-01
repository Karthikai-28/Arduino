// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const byte encoder1 = 3;
const byte encoder2 = 2;

const float stepcount = 40;
//unsigned float z = a.acceleration.x;
const float wheeldia = 100;

volatile int counter_A = 0;
volatile int counter_B = 0;

//Motor1

int DIR1 = 12;
int PWM1 = 10;

//Motor2

int DIR2 = 11;
int PWM2 = 9;

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

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;
void setup(void) {
  Serial.begin(115200);
  push();
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

}

void loop() {

  /* first show some 'normal' readings */


  for (uint16_t i = 0; i < 300; i++) {
    printAvailableData();
    delay(10);
  }

  /* Next, turn on cycle mode. Note how this changes how often the
   *  readings are updated.
   *
   *  First set a slow cycle rate so the effect can be seen clearly.
   */

  mpu.setCycleRate(MPU6050_CYCLE_20_HZ);
  /* ensure that sleep mode is not active. Cycle mode only works
   *  as intended while sleep mode is not active */
 

  for (uint16_t i = 0; i < 300; i++) {
    printAvailableData();
    delay(10);
  }

  /* Finally enable sleep mode. Note that while we can still fetch
   *  data from the measurement registers, the measurements are not
   *  updated. In sleep mode the accelerometer and gyroscope are
   *  deactivated to save power, so measurements are halted.
   */
    
  for (uint16_t i = 0; i < 300; i++) {
    
    printAvailableData();
    delay(10);
  }
    
}

void printAvailableData(void) {

  /* Populate the sensor events with the readings*/
  mpu.getEvent(&a, &g, &temp);
//    while(a.acceleration.x >= 2.00){
//          Forward(10200,100);
//          delay(1000);
//          if(a.acceleration.y <= -0.20){
//            spinright(1340, 100);
//            delay(1000);
//          }
//          else{
//            Stop(0,0);
//            
//          }
//  }
if (a.acceleration.x >= 2.30){

  Forward(5100, 100);
  delay(100);
  spinright(1000,100);
}
if (a.acceleration.y >= -3.60){

  Forward(5100, 100);
  delay(100);
  spinright(1000,100);
}
if (a.acceleration.y >= -3.80){

  Forward(5100, 100);
  delay(100);
  spinright(1000,100);
}
if (a.acceleration.y >= -3.0){

  Forward(5100, 100);
  delay(100);
  spinright(1000,100);
}

  /* Print out acceleration data in a plotter-friendly format */
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print(a.acceleration.z);
  Serial.println("");
  delay(1000);
}

void push(){
    pinMode(DIR1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(encoder1, INPUT);
  pinMode(encoder2, INPUT);
  attachInterrupt(digitalPinToInterrupt (encoder1), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt (encoder2), ISR_countB, RISING);
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
