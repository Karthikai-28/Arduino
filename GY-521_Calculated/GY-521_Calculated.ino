#include <Wire.h>              // This library allows you to communicate with I2C devices.

const int MPU_ADDRESS = 0x68;  // I2C Address for GY-521 which have Accelerometer, Gyroscope, Temperature and Motion detection

                              // If AD0 pin in the sensor is HIGH, then address will be 0x69. Now, it is in LOW condition, so it is 0x68

float accelerometer_x, accelerometer_y, accelerometer_z = 0;   //X,Y,Z variables of the Accelerometer

float gyroscope_x, gyroscope_y, gyroscope_z = 0;              //X,Y,Z variables of the Gyroscope 

float accelerometerAngle_X, accelerometerAngle_Y, gyroscopeAngle_X, gyroscopeAngle_Y, gyroscopeAngle_Z = 0;

float Roll, Pitch, Yaw = 0;

float accelerometer_Error_X, accelerometer_Error_Y, gyroscope_Error_X, gyroscope_Error_Y, gyroscope_Error_Z = 0;

float elapsedTime, currentTime, previousTime = 0;

int c = 0;



void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDRESS);      //Begins a Transmission to the I2C slave
  Wire.write(0x6B);                         //PWR_MGMT_1 Register
  Wire.write(0x00);                         //Set to zero (This command wakes up the MPU-6050)
  Wire.endTransmission(true);               //End the Transmission
  calculate_IMU_error();                    //Calling this function to get the IMU error values
  delay(20); 

  /*
   * Configure Aceelerometer Sensitivity - Full Scale Range (default +/-2g)
   * Wire.beginTransmission(MPU_ADDRESS);
   * Wire.write(0x1C);                      //Talk to the ACCEL_CONFIG register (1C hex)
   * Wire.write(0x10);                      //Set the register bite as 00010000(+/- 8g full scale range)
   * Wire.endTransmission(true);               
   */

   /*
    * Configure Gyro sensivity - Full scale range (default +/- 250 deg/s)
    * Wire.begintransmission(MPU_ADDRESS)
    * Wire.write(0x1B);                    //Talk to the GYRO_CONFIG register (1B hex)
    * Wire.write(0x10);                    //Set the register bits as 00010000 (1000deg/s full scale)
    * Wire.endTransmission(true);
    * delay(10);
    */
}

void loop()
{
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);                         //Starting with register 0x3B(ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and descriptions revision 4.2, p.40]
  Wire.endTransmission(false);              //The parameter indicates that the Arduini will restart the sensor. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDRESS, 7*2, true); //Request a total of 7*2=14 registers

  //"Wire.read()<<8 | Wire.read();" Means two registers are read and stored in the same variable


 //Accelerometer
  
  
  //For a range of +-2g, we need to divide the raw values by 16384.0 (According to the Datasheet)
  accelerometer_x = (Wire.read()<<8 | Wire.read()) / 16384.0; //Reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = (Wire.read()<<8 | Wire.read()) / 16384.0; //Reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = (Wire.read()<<8 | Wire.read()) / 16384.0; //Reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

  accelerometerAngle_X = (atan(accelerometer_x / sqrt(pow(accelerometer_x, 2) + pow(accelerometer_z, 2)) * 180 / PI)) - 0.58;
  //accelerometerAngle_X ~ 0.58. See the calculate_IMU_error() custom function for more details

  accelerometerAngle_Y = (atan(-1 * accelerometer_x / sqrt(pow(accelerometer_y, 2) + pow(accelerometer_z, 2))) * 180 / PI ) + 1.58;
  //accelerometerAngle_Y ~ -1.58



 //Gyroscope


  previousTime = currentTime;                              //Previous Time is stored before the actual time read

  currentTime = millis();                                  //Current time actual time read

  elapsedTime = (currentTime - previousTime) / 1000;       //Divide by 1000 to get Seconds

  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x43);                                        //gyroscope data first register address 0x43
  Wire.write(false);
  Wire.requestFrom(MPU_ADDRESS, 7*2, true);                      // Read 7*2=14 registers total, each axis value is stores in 2 registers
  

  //For a 250 deg/s range we have to divide the raw values by 131.0 (According to the Datasheet)
  gyroscope_x = (Wire.read()<<8 | Wire.read()) / 131.0;     //Reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyroscope_y = (Wire.read()<<8 | Wire.read()) / 131.0;     //Reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyroscope_z = (Wire.read()<<8 | Wire.read()) / 131.0;     //Reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  //Correct the outpu with the calculated error values

  gyroscope_x = gyroscope_x + 0.56;                         //Gyroscope_Error_X ~ (-0.56)
  gyroscope_y = gyroscope_y - 2;                            //Gyroscope_Error_Y ~ (+2)
  gyroscope_z = gyroscope_z + 0.79;                         //Gyroscope_Error_Z ~ (-0.79)


  //Curently the raw values are in degrees er seconds(deg/s), so we need to multiply by seconds(s) to get the angle in degrees
  gyroscopeAngle_X = gyroscopeAngle_X + gyroscope_x * elapsedTime;    //deg/s * s = deg
  gyroscopeAngle_Y = gyroscopeAngle_Y + gyroscope_y * elapsedTime;  

  Yaw = Yaw + gyroscope_z * elapsedTime;
  //Complemetary filter - combine Accelerometer and Gyroscope Angle values

  Roll = 0.96 * gyroscopeAngle_X + 0.04 * accelerometerAngle_X;
  Pitch = 0.96 * gyroscopeAngle_Y + 0.04 * accelerometerAngle_Y;
   

 

//  Serial.print(" | Roll ");
//  Serial.print(Roll);
//  Serial.print(" | Pitch ");
//  Serial.print(Pitch);  
//  Serial.print(" | Yaw ");
//  Serial.print(Yaw);
//  Serial.println();
//
//  delay(1000);

  Serial.print("aAngle_X = ");
  Serial.print(accelerometerAngle_X);
  Serial.print(" | aAngle_Y = ");
  Serial.print(accelerometerAngle_Y);

  Serial.print(" | aX = ");
  Serial.print(accelerometer_x);
  Serial.print(" | aY = ");
  Serial.print(accelerometer_y);
  Serial.print(" | aZ = ");
  Serial.print(accelerometer_z);

  Serial.print(" | gX = ");
  Serial.print(gyroscope_x);
  Serial.print(" | gY = ");
  Serial.print(gyroscope_y);
  Serial.print(" | gZ = ");
  Serial.print(gyroscope_z);
  Serial.println();

  delay(1000);
  
}

void calculate_IMU_error()
{
  //We can call this function in the setup section to calculate the Accelerometer and Gyroscope data error.
  //From here we will get the error cvalues used in the above equation printed in the Serial Monitor.
  //Note that we shoud place the IMU flat in order to get the proper values, so that we then can correct the values.
  //Read the Accelerometer values for 200 times.
  while(c < 200){
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDRESS, 7*2, true);
    accelerometer_x = (Wire.read() << 8 | Wire.read()) / 16384.0;
    accelerometer_y = (Wire.read() << 8 | Wire.read()) / 16384.0;
    accelerometer_z = (Wire.read() << 8 | Wire.read()) / 16384.0;

    accelerometerAngle_X = (atan(accelerometer_x / sqrt(pow(accelerometer_x, 2) + pow(accelerometer_z, 2)) * 180 / PI)) - 0.58;
  

    accelerometerAngle_Y = (atan(-1 * accelerometer_x / sqrt(pow(accelerometer_y, 2) + pow(accelerometer_z, 2))) * 180 / PI ) + 1.58;

    c++;
  }
  accelerometer_Error_X = accelerometer_Error_X / 200;
  accelerometer_Error_Y = accelerometer_Error_Y / 200;
  c = 0;

  while (c < 200){
    Wire.beginTransmission(MPU_ADDRESS);
    Wire.write(0x43);                                        
    Wire.write(false);
    Wire.requestFrom(MPU_ADDRESS, 7*2, true);                      
  

    gyroscope_x = (Wire.read()<<8 | Wire.read()) / 131.0;    
    gyroscope_y = (Wire.read()<<8 | Wire.read()) / 131.0;    
    gyroscope_z = (Wire.read()<<8 | Wire.read()) / 131.0;

    //Sum all Readings
    gyroscope_Error_X = gyroscope_Error_X + gyroscope_x;
    gyroscope_Error_Y = gyroscope_Error_Y + gyroscope_y;
    gyroscope_Error_Z = gyroscope_Error_Z + gyroscope_z;
    c++;
  }
  //Divide the sum by 200 to get the error value
  gyroscope_Error_X = gyroscope_Error_X / 200;
  gyroscope_Error_Y = gyroscope_Error_Y / 200;
  gyroscope_Error_Z = gyroscope_Error_Z / 200;


}
