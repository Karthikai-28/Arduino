#include <Wire.h>              // This library allows you to communicate with I2C devices.

const int MPU_ADDRESS = 0x68;  // I2C Address for GY-521 which have Accelerometer, Gyroscope, Temperature and Motion detection

                              // If AD0 pin in the sensor is HIGH, then address will be 0x69. Now, it is in LOW condition, so it is 0x68

int16_t accelerometer_x, accelerometer_y, accelerometer_z;   //X,Y,Z variables of the Accelerometer

int16_t accelerometerx, accelerometery, accelerometerz;

int16_t gyroscope_x, gyroscope_y, gyroscope_z;              //X,Y,Z variables of the Gyroscope 

int16_t temperature;                                       //Temperature initialization to test the temperature around the sensor

char Temperature_String[7];  //Temporary Variable used in convert function

char* convert_int16_to_str(int16_t i)                   //Converts int16 to string. Moreover, resulring strings will have the same length in the debug monitor
{
  sprintf(Temperature_String, "%6d", i);
  return Temperature_String;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDRESS);      //Begins a Transmission to the I2C slave
  Wire.write(0x6B);                         //PWR_MGMT_1 Register
  Wire.write(0x00);                         //Set to zero (This command wakes up the MPU-6050)
  Wire.endTransmission(true);               //End the Transmission
}

void loop()
{
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);                         //Starting with register 0x3B(ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and descriptions revision 4.2, p.40]
  Wire.endTransmission(false);              //The parameter indicates that the Arduini will restart the sensor. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDRESS, 7*2, true); //Request a total of 7*2=14 registers

  //"Wire.read()<<8 | Wire.read();" Means two registers are read and stored in the same variable


 //Accelerometer
  
  
  accelerometer_x = (Wire.read()<<8 | Wire.read()); //Reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = (Wire.read()<<8 | Wire.read()); //Reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = (Wire.read()<<8 | Wire.read()); //Reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  for(float acceleration = 0; acceleration < 2000; acceleration++){
    accelerometerx += accelerometer_x;
    accelerometery += accelerometer_y;
    accelerometerz += accelerometer_z;
  delay(5);
  }
  accelerometerx = accelerometer_x/2000;
  accelerometery = accelerometer_y/2000;
  accelerometerz = accelerometer_z/2000;



 //Gyroscope


  gyroscope_x = (Wire.read()<<8 | Wire.read());     //Reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyroscope_y = (Wire.read()<<8 | Wire.read());     //Reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyroscope_z = (Wire.read()<<8 | Wire.read());     //Reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
   

  temperature = Wire.read()<<8 | Wire.read();     //Reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)

  Serial.print("aX = ");
  Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = ");
  Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = ");
  Serial.print(convert_int16_to_str(accelerometer_z));

  Serial.print(" | gX = ");
  Serial.print(convert_int16_to_str(gyroscope_x));
  Serial.print(" | gY = ");
  Serial.print(convert_int16_to_str(gyroscope_y));
  Serial.print(" | gZ = ");
  Serial.print(convert_int16_to_str(gyroscope_z));

  Serial.print(" | Temperature ");
  Serial.print(temperature/340.00+36.53);
  Serial.println();

  delay(1000);
  
}
