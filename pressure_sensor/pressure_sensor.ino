 #include <Servo.h>
 Servo servo;
 int reading;   
 
void setup(void) {
 Serial.begin(9600);   
 servo.attach(9); //servo at digital pin 9
 servo.write(0); //initial point for servo

}
 
void loop(void) {
  reading = analogRead(A0); //attached to analog 0
  Serial.print("Sensor value = ");
  Serial.println(reading);
 
int value = map(reading, 0, 1023, 0, 255);

  servo.write(value);
 
  delay(100);
}
