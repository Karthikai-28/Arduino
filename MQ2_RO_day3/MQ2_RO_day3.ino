void setup() {
  Serial.begin(9600); 
}

void loop() {
  float sensor_volt;
  float RS_air; 
  float R0; 
  float sensorValue; 
  for (int x = 0 ; x < 500 ; x++) 
  {
    sensorValue = sensorValue + analogRead(A0);
    Serial.println(sensorValue);
  }
  sensorValue = sensorValue / 500.0; //Take average of readings
  sensor_volt = sensorValue * (5.0 / 1023.0); //Convert average to voltage
  RS_air = ((5.0 * 10.0) / sensor_volt) - 10.0; //Calculate RS in fresh air
  R0 = RS_air / 4.4; //Calculate R0

  Serial.print("R0 = "); 
  Serial.println(R0);
  delay(1000); 
}
