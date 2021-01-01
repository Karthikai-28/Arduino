#include <Wire.h>              // This library allows you to communicate with I2C devices.

const int MPU_ADDRESS = 0x68;  // I2C Address for GY-521 which have Accelerometer, Gyroscope, Temperature and Motion detection

                              // If AD0 pin in the sensor is HIGH, then address will be 0x69. Now, it is in LOW condition, so it is 0x68

float accelerometer_x, accelerometer_y, accelerometer_z, Accelerometer_Total_Vector;   //X,Y,Z variables of the Accelerometer

float gyroscope_x, gyroscope_y, gyroscope_z;              //X,Y,Z variables of the Gyroscope 

float accelerometerAngle_X, accelerometerAngle_Y, gyroscopeAngle_X, gyroscopeAngle_Y, gyroscopeAngle_Z;

float Roll, Pitch, Yaw;

float accelerometer_Error_X, accelerometer_Error_Y, gyroscope_Error_X, gyroscope_Error_Y, gyroscope_Error_Z;

float elapsedTime, currentTime, previousTime;

long gyroscope_X_Calibration, gyroscope_Y_Calibration, gyroscope_Z_Calibration; 

long Angle_Pitch_accelerometer, Angle_Roll_accelerometer;

unsigned long current_millis;

boolean Set_gyroscope_Angle;

float Angle_Pitch, Angle_Roll;

float Angle_Pitch_Output, Angle_Roll_Output;

long loop_timer;

unsigned long Last_Time;

float Input, Output; 

unsigned long Current_Millis;

unsigned long Previous_Millis = 0;

unsigned long Interval = 50;

int Sample_Time = 10;  //0.01 seconds

int c = 0;



void setup()
{
  Serial.begin(9600);
  Wire.begin();
  
  Register_Setup();

  for(int cal_int = 0; cal_int < 2000; cal_int++){
    Read_MPU();
    gyroscope_X_Calibration += gyroscope_x;
    gyroscope_Y_Calibration += gyroscope_y;
    gyroscope_Z_Calibration += gyroscope_z;
    delay(5);
  }
  gyroscope_X_Calibration /= 2000;
  gyroscope_Y_Calibration /= 2000;
  gyroscope_Z_Calibration /= 2000;  

  loop_timer = micros();
  Computation();
}

void loop()
{
  current_millis = millis();

  Read_MPU();

  gyroscope_x -= gyroscope_X_Calibration;       //Subtract the Offset calibration value from the raw gyroscope_x value
  gyroscope_y -= gyroscope_Y_Calibration;       //Subtract the offset calibration value from the raw gyroscope_y value
  gyroscope_z -= gyroscope_Z_Calibration;       //Subtract the offset calibration value from the raw gyroscope_z value

  //Gyroscope Angle Calibration      
  //1 / (250Hz / 65.5) = 0.0000611
  Angle_Pitch += (gyroscope_x * 0.0000611);       //Calculate the travelled pitch angle and add this to the Angle_Pitch variable
  Angle_Roll += (gyroscope_y * 0.0000611);        //Calculate the travelled roll angle and add this to the Angle_Roll variable


  //0.0000611 * ((PI) / 180deg) = 0.000001066. The Arduino sin funstion is in radians
  Angle_Pitch += Angle_Roll * sin(gyroscope_z * 0.000001066);   //If the IMU has yawed transfer the roll angle to the pitch angle
  Angle_Roll -= Angle_Pitch * sin(gyroscope_z * 0.000001066);   //If the IMU has yawed transfer the pitch angle to the roll angle

  //Accelerometer Angle Calibration

  Accelerometer_Total_Vector = sqrt(pow(accelerometer_x, 2) + pow(accelerometer_y, 2) + pow(accelerometer_z, 2));   //Calculate the total accelerometer vector

  //1 / ((PI) / 180) = 57.296 The Arduino asin function is in radians
  Angle_Pitch_accelerometer = asin((float)accelerometer_y / Accelerometer_Total_Vector) * 57.296;    //Calculate the Pitch Angle
  Angle_Roll_accelerometer = asin((float)accelerometer_x / Accelerometer_Total_Vector) * -57.296;    //Calculate the Roll Angle


  //Place the Sensor spirit level and note the values in the following two lines for Calibration
  Angle_Pitch_accelerometer -=0;     //Accelerometer Calibration value for Pitch
  Angle_Roll_accelerometer -=0;      //Accelerometer Calibration value for Roll


  if(Set_gyroscope_Angle){                                                           //If the IMU is already started
    Angle_Pitch = (Angle_Pitch * 0.9966) + (Angle_Pitch_accelerometer * 0.0004);         //Correct the drift of the gyroscope picth angle with accelerometer pitch angle
    Angle_Roll = (Angle_Roll * 0.9966) + (Angle_Roll_accelerometer * 0.0004);            //Correct the drift of the gyroscope roll angle with accelerometer roll angle
  }
  else{                                                                              //At the Initial start
    Angle_Pitch = Angle_Pitch_accelerometer;                                          //Set the gyroscope pitch angle equal to the accelerometer pitch angle
    Angle_Roll = Angle_Roll_accelerometer;                                           //Set the gyroscope roll angle equal to the accelerometer roll angle
    Set_gyroscope_Angle = true;                                                      //Set the IMU started flag
  }


  //To dampen the pitch and roll angles a complementary filter is used
  Angle_Pitch_Output = (Angle_Pitch_Output * 0.9) + (Angle_Pitch + 0.1);                 //Take 90% of the output pitch value and add 10% of the raw pitch value
  Angle_Roll_Output = (Angle_Roll_Output * 0.9) + (Angle_Roll + 0.1);                    //Take 90% of the output roll value and add 10% of the raw roll value

  while(micros() - loop_timer < 400);      //Wait until the loop timer reaches 400us(250Hz) before starting the nect loop
  loop_timer = micros();                   //Reset the loop timer  
//  Serial.print(" | Roll ");
//  Serial.print(Roll);
//  Serial.print(" | Pitch ");
//  Serial.print(Pitch);  
//  Serial.print(" | Yaw ");
//  Serial.print(Yaw);
//  Serial.println();
//
//  delay(1000);



  Serial.print("aX = ");
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
    accelerometer_x = (Wire.read() << 8 | Wire.read());
    accelerometer_y = (Wire.read() << 8 | Wire.read());
    accelerometer_z = (Wire.read() << 8 | Wire.read());

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
  

    gyroscope_x = (Wire.read()<<8 | Wire.read());    
    gyroscope_y = (Wire.read()<<8 | Wire.read());    
    gyroscope_z = (Wire.read()<<8 | Wire.read());

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

void Read_MPU()
{
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);                         //Starting with register 0x3B(ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and descriptions revision 4.2, p.40]
  Wire.endTransmission(false);              //The parameter indicates that the Arduini will restart the sensor. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDRESS, 7*2, true); //Request a total of 7*2=14 registers

  //"Wire.read()<<8 | Wire.read();" Means two registers are read and stored in the same variable


 //Accelerometer
  
      //For a range of +-2g, we need to divide the raw values by 16384.0 (According to the Datasheet)
      accelerometer_x = (Wire.read()<<8 | Wire.read()); //Reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
      accelerometer_y = (Wire.read()<<8 | Wire.read()); //Reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
      accelerometer_z = (Wire.read()<<8 | Wire.read()); //Reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

     
       Wire.beginTransmission(MPU_ADDRESS);
       Wire.write(0x43);                                        //gyroscope data first register address 0x43
       Wire.write(false);
       Wire.requestFrom(MPU_ADDRESS, 7*2, true);                      // Read 7*2=14 registers total, each axis value is stores in 2 registers
  

       //For a 250 deg/s range we have to divide the raw values by 131.0 (According to the Datasheet)
       gyroscope_x = (Wire.read()<<8 | Wire.read());     //Reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
       gyroscope_y = (Wire.read()<<8 | Wire.read());     //Reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
       gyroscope_z = (Wire.read()<<8 | Wire.read());     //Reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

}

void Register_Setup(){
  Wire.beginTransmission(MPU_ADDRESS);      //Begins a Transmission to the I2C slave
  Wire.write(0x6B);                         //PWR_MGMT_1 Register
  Wire.write(0x00);                         //Set to zero (This command wakes up the MPU-6050)
  Wire.endTransmission(true);               //End the Transmission
  calculate_IMU_error();                    //Calling this function to get the IMU error values
  delay(20); 

  
  //Configure Aceelerometer Sensitivity - Full Scale Range (default +/-2g)
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x1C);                      //Talk to the ACCEL_CONFIG register (1C hex)
  Wire.write(0x10);                      //Set the register bite as 00010000(+/- 8g full scale range)
  Wire.endTransmission(true);               
  

  
  //Configure Gyro sensivity - Full scale range (default +/- 250 deg/s)
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x1B);                    //Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x10);                    //Set the register bits as 00010000 (1000deg/s full scale)
  Wire.endTransmission(true);
  delay(10);
}

void Computation()
{
  unsigned long now = millis();
  int Time_Change = (now - Last_Time);
  if(Time_Change >= Sample_Time){
    Input = Angle_Pitch_Output;
    Last_Time = now;
  }
  if((Current_Millis - Previous_Millis) >= Interval)
  {
    Serial.print("Input ");
    Serial.println(Input);

    Previous_Millis = millis();
  }
}
