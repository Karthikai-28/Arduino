const int trigPin = 9;
const int echoPin = 10;
const int bulb = 6;
long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(bulb, OUTPUT);
Serial.begin(9600); 
}
void loop() {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
if (distance <20)
{
  digitalWrite(6,HIGH);
  
}
else if(distance>20)
{
digitalWrite(6,LOW);
}
Serial.print("Distance: ");
Serial.println(distance);
delay(200);
}

