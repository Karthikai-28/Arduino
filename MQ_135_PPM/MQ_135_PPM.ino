int led = 10; 
int buzzer = 9; 
int gas_sensor = A0; 
float m = 116.6020682; // Slope
float b = -2.769034857;  // Y-Intercept
float R0 = 25.5; // Resistance of sensor in fresh air

void setup() {
  Serial.begin(9600); 
  pinMode(led, OUTPUT); 
  digitalWrite(led, LOW); 
  pinMode(gas_sensor, INPUT); 
}

void loop() {
  
  float sensor_volt;
  float RS_gas; 
  float ratio; 
  float sensorValue = analogRead(gas_sensor); 
  sensor_volt = sensorValue * (5.0 / 1023.0); 
  RS_gas = ((5.0 * 10.0) / sensor_volt) - 10.0; 
  ratio = RS_gas / R0;  

  double ppm = m*pow((ratio),b);  
  double percentage = ppm / 1000; 
  Serial.print("PPM = ");
  Serial.println(ppm);
  Serial.print(percentage);
  Serial.println("%"); 
 

  if (ppm > 350) {
    digitalWrite(led, HIGH); 
  } else {

    digitalWrite(led, LOW);
  }
}
