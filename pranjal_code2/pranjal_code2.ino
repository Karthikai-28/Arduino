int motor1 = 7;
int motor2 = 6;
int motorpwm1 = 10;
int motorpwm2 = 11;
 
int encoder = 3;
 
volatile unsigned int counter;
int rpm;
 
void setup() {
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motorpwm1, OUTPUT);
  pinMode(motorpwm2, OUTPUT);
  pinMode(encoder, INPUT);
 
  digitalWrite(encoder, HIGH);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  analogWrite(motorpwm1, 100);
  analogWrite(motorpwm2, 100);
  
  attachInterrupt(0,countpulse,RISING);
}
 
void countpulse(){
        counter++;
}
 
void loop() {
  static uint32_t previousMillis;
  if (millis() - previousMillis >= 1000) {
            rpm = (counter/20)*60;          
            counter = 0;
            previousMillis += 1000;
  }
 
  if(Serial.available()>0)
  {
    Serial.print("Speed: ");
    Serial.print(rpm);
    Serial.print(" rps");
    delay(1);
  }
}
