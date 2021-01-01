float Sensor=0;

void setup()
{
  Serial.begin(9600);
  
  SensorGas.setBoardMode(SENS_ON);
  delay(1000);
  SensorGas.configureSensor(SENS_CO2,1);
  SensorGas.setSensorMode(SENS_ON, SENS_CO2);
}

void loop(){
  
  delay(30000);
  
  Sensor = SensorGas.readValue(SENS_CO2);
  Serial.println(Sensor);
  Sensor=0;
  
} 
