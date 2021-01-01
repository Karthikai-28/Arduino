float sensorValue;
float sensorVolts;
 
void setup()
{
 Serial.begin(9600);      // sets the serial port to 9600
 delay(2000);    // allow the MQ-6 to warm up
}
 
void loop()
{
 
 for(int i = 0; i < 100; i++){
     sensorValue = sensorValue + analogRead(0);       // read analog input pin 0
 }
 
 sensorValue = sensorValue / 100;                  // get average reading
 sensorVolts = sensorValue/1024*5.0;   //convert to voltage
 Serial.println(sensorVolts);  // prints the value read
 delay(100);                        // wait 100ms for next reading
}
