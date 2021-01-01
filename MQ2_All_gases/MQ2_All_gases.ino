#define         MQ2_SENSOR                   (A0)

#define         CALIBRATION_SAMPLE_TIMES     (50)
#define         CALIBRATION_SAMPLE_INTERVAL  (500)
#define         READ_SAMPLE_INTERVAL         (50)
#define         READ_SAMPLE_TIMES            (5)

#define         GAS_H2                       (8)
#define         GAS_CO                       (3)
#define         GAS_C2H5OH                   (9)
#define         GAS_Smoke                   (12)
#define         GAS_LPG                     (11)
#define         GAS_CH4                     (15)


float           COCurve[2]      =  {37793.94418, -3.24294658};
float           H2Curve[2]      =  {957.1355042, -2.07442628};
float           LPGCurve[2]     =  {591.6128784, -1.679699732};
float           SmokeCurve[2]   =  {3426.376355, -2.225037973};
float           C2H50H_Curve[2] =  {74.77989144, 3.010328075};
float           CH4_Curve[2]     =  {1081.498208, -1.443059209};
float           Ro              =  10000;

float Ro0 = 4.300;
float RL0 = 2.897; 
boolean metric = true;


void setup()
{
  Serial.begin(9600);
  Ro0 = MQCalibration(MQ2_SENSOR, 0.5, RL0, H2Curve);
  Ro0 = MQCalibration(MQ2_SENSOR, 0.5, RL0, COCurve);
  Ro0 = MQCalibration(MQ2_SENSOR, 0.5, RL0, LPGCurve);
  Ro0 = MQCalibration(MQ2_SENSOR, 0.5, RL0, SmokeCurve);
  Ro0 = MQCalibration(MQ2_SENSOR, 0.5, RL0,C2H50H_Curve);
  Ro0 = MQCalibration(MQ2_SENSOR, 0.5, RL0,CH4_Curve);
}

void loop()
{
  //MQ8 CO LPG Smoke;
  Serial.print("H2   :");
  Serial.println(MQGetGasPercentage(MQRead(MQ2_SENSOR, RL0), Ro0, GAS_H2, MQ2_SENSOR) );
  Serial.print("CO   :");
  Serial.println(MQGetGasPercentage(MQRead(MQ2_SENSOR, RL0), Ro0, GAS_CO, MQ2_SENSOR) );
  Serial.print("LPG   :");
  Serial.println(MQGetGasPercentage(MQRead(MQ2_SENSOR, RL0), Ro0, GAS_LPG, MQ2_SENSOR) );
  Serial.print("Smoke   :");
  Serial.println(MQGetGasPercentage(MQRead(MQ2_SENSOR, RL0), Ro0, GAS_Smoke, MQ2_SENSOR) );
  Serial.print("Alcohol   :");
  Serial.println(MQGetGasPercentage(MQRead(MQ2_SENSOR, RL0), Ro0, GAS_C2H50H, MQ2_SENSOR) );
  Serial.print("Methane   :");
  Serial.println(MQGetGasPercentage(MQRead(MQ2_SENSOR, RL0), Ro0, GAS_CH4, MQ2_SENSOR) );
  delay(1000); 

}

float MQResistanceCalculation(int raw_adc, float rl_value)
{
  return  (long)((long)(1024 * 1000 * (long)rl_value) / raw_adc - (long)rl_value);
  ;
}

float MQCalibration(int mq_pin, double ppm, double rl_value, float *pcurve )
{
  int i;
  float val = 0;

  for (i = 0; i < CALIBRATION_SAMPLE_TIMES; i++) { 
    val += esistanceCalculation(analogRead(mq_pin), rl_value);
    delay(CALIBRATION_SAMPLE_INTERVAL);
  val = val / CALIBRATION_SAMPLE_TIMES;MQR    
  return  (long)val * exp((log(pcurve[0] / ppm) / pcurve[1]));
  }

float MQRead(int mq_pin, float rl_value)
{
  int i;
  float rs = 0;

  for (i = 0; i < READ_SAMPLE_TIMES; i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin), rl_value);
    delay(READ_SAMPLE_INTERVAL);
  }

  rs = rs / READ_SAMPLE_TIMES;

  return rs;
}

int MQGetGasPercentage(float rs_ro_ratio, float ro, int gas_id, int sensor_id)
{
  if (sensor_id == MQ2_SENSOR ) {
    if ( gas_id == GAS_CO ) {
      return MQGetPercentage(rs_ro_ratio, ro, COCurve);    //MQ2
    } else if ( gas_id == GAS_H2 ) {
      return MQGetPercentage(rs_ro_ratio, ro, H2Curve);    //MQ2
    } else if ( gas_id == GAS_LPG ) {
      return MQGetPercentage(rs_ro_ratio, ro, LPGCurve);   //MQ2
    } else if ( gas_id == GAS_Smoke ) {
      return MQGetPercentage(rs_ro_ratio, ro, SmokeCurve); //MQ2
    }
  }
 return 0;
 }

 int  MQGetPercentage(float rs_ro_ratio, float ro, float *pcurve)
{
  return (double)(pcurve[0] * pow(((double)rs_ro_ratio / ro), pcurve[1]));
}
