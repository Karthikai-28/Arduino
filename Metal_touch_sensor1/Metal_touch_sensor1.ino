const int SensorPin = 7;
const int analogIn = A0;
const int ledPin = 13;

int SensorState=0;
int analogVal = 0;

void setup()
{
pinMode(SensorPin,INPUT);
pinMode(ledPin,OUTPUT);
}

void loop()
{
analogVal = analogRead(analogIn);
SensorState=digitalRead(SensorPin);
if(SensorState==HIGH)
{
digitalWrite(ledPin,HIGH);
}
else
{
digitalWrite(ledPin,LOW);
}
}
