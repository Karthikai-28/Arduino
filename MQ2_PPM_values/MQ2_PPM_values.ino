#define MQ_PIN (A0)
#define RL_VALUE (5)
#define RO_CLEAN_AIR_FACTOR (9.83)


#define CALIBRATION_SAMPLE_TIMES (300)
#define CALIBRATION_SAMPLE_INTERVAL (60)

#define READ_SAMPLE_INTERVAL (5)
#define READ_SAMPLE_TIMES (5)


#include<math.h>



void setup()
{
  Serial.begin(9600);
  Serial.print("Calibrating...\n");
  Serial.print("This will take approx");
  Serial.print(CALIBRATION_SAMPLE_TIMES * CALIBRATION_SAMPLE_INTERVAL / 1000);
  Serial.print("second \n");
  

  Serial.print("Calibration is done...\n");
}

void loop()
{
  float sensor_volt;
  float RS_air;
  float R0;
  float ratio;
  float sensor_value;
  float b;
  float *pcurve;

  for(int x=0; x<100; x++)
  {
    sensor_value = sensor_value + analogRead(A0);
  }
  sensor_value = sensor_value/100;

  sensor_volt = sensor_value/1024*5;

  Serial.print("sensor_volt = ");
  Serial.println(sensor_volt);
  delay(500);
  
  RS_air = (5-sensor_volt)/sensor_volt;

  Serial.print("RS_air = ");
  Serial.println(RS_air);
  delay(500);
  
  R0 = RS_air/9.8;

  Serial.print("R0 = ");
  Serial.println(R0);
  delay(500);
  
  sensor_value = analogRead(A0);
  sensor_volt=(float)sensor_value/1024*5;
  RS_air = (5-sensor_volt)/sensor_volt;
  ratio = RS_air/R0;
  
  Serial.print("Ratio = ");
  Serial.println(ratio);
  delay(500);

  b = (pow(10,(((log(ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));


 
  Serial.print("PPM_value = ");
  Serial.println(b);
  delay(1000);

  
}

