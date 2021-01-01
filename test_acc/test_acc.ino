
#include <Wire.h>



long acc_x, acc_y, acc_z, acc_total_vector;
long acc_x_cal, acc_y_cal, acc_z_cal;
long loop_timer;
float angle_roll_acc, angle_pitch_acc, acc_roll_cal, acc_pitch_cal;
float angle_pitch_output, angle_roll_output;
unsigned long lastTime;
float Input, Output, Input_x;
double Iterm, lastErr;
double Setpoint;
double error;
double dErr;
int SampleTime = 10; //0.01 sec
double SampleTimeInSec = ((double)SampleTime)/1000;
unsigned long current_millis; 
unsigned long previous_millis = 0; 
unsigned long interval = 50; 
long lastDebounceTime = 0;  
long debounceDelay = 1000;   

void setup() {
  Wire.begin();                                                        //Start I2C as master
  Serial.begin(9600);                                                 //Use only for debugging
   setup_mpu_6050_registers();   //Setup the registers of the MPU-6050 (500dfs / +/-8g) and start the gyro
   Serial.println("Setpoint, Sensor, Output");
   
  
}

void loop(){

  for (int cal_int = 0; cal_int < 2000 ; cal_int ++){                
    read_mpu_6050_data();                                            
    acc_x_cal += acc_x;                                              
    acc_y_cal += acc_y;                                              
    acc_z_cal += acc_z;                                              
    delay(3);                                                         
  }
  acc_x_cal /= 2000;                                                  
  acc_y_cal /= 2000;                                                  
  acc_z_cal /= 2000;                                                  

  loop_timer = micros(); 

    for (int cal = 0; cal < 2000 ; cal ++){                
    read_mpu_6050_data();                                            
    acc_pitch_cal += angle_pitch_acc;                                              
    acc_roll_cal += angle_roll_acc;                                                                                           
    delay(3);                                                         
  }
  acc_pitch_cal /= 2000;                                                  
  acc_roll_cal /= 2000;                                                                                                    

  loop_timer = micros(); 
  
  current_millis = millis();

  read_mpu_6050_data();                                                //Read the raw acc and gyro data from the MPU-6050

  acc_x -= acc_x_cal;                                                //Subtract the offset calibration value from the raw gyro_x value
  acc_y -= acc_y_cal;                                                //Subtract the offset calibration value from the raw gyro_y value
  acc_z -= acc_z_cal;                                                //Subtract the offset calibration value from the raw gyro_z value
  
                                                                       //Gyro angle calculations
                                                                       //0.0000611 = 1 / (250Hz / 65.5)
  
  while(micros() - loop_timer < 4000);                                 //Wait until the loop_timer reaches 4000us (250Hz) before starting the next loop
  loop_timer = micros();                                               //Reset the loop timer


  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
                                                                       //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;       //Calculate the pitch angle
  angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;
                                                                       
  if ((current_millis - previous_millis) >= interval)
{
  

     Serial.print("X - axis = ");
     Serial.print(acc_pitch_cal);
     Serial.print(" | ");
     Serial.print("Y - axis = ");
     Serial.print(acc_roll_cal);
     Serial.println("");
     
     previous_millis = millis();
} 
}


void read_mpu_6050_data(){                                             //Subroutine for reading the raw gyro and accelerometer data
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x3B);                                                    //Send the requested starting register
  Wire.endTransmission();                                              //End the transmission
  Wire.requestFrom(0x68,14);                                           //Request 14 bytes from the MPU-6050
  while(Wire.available() < 14);                                        //Wait until all the bytes are received
  acc_x = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_x variable
  acc_y = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_y variable
  acc_z = Wire.read()<<8|Wire.read();                                  //Add the low and high byte to the acc_z variable
  
}

void setup_mpu_6050_registers(){
  //Activate the MPU-6050
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x6B);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);                                        //Start communicating with the MPU-6050
  Wire.write(0x1C);                                                    //Send the requested starting register
  Wire.write(0x00);                                                    //Set the requested starting register
  Wire.endTransmission();                                              //End the transmission
}
