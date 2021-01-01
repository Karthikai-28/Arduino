#include <Wire.h>
#include <DFRobot_QMC5883.h>

DFRobot_QMC5883 compass;
int heading=0;
int rbm =5;
int lbm =6;
int mbr2 = 4;
int mbr1 = 7;
int pwm1 = 10;
int pwm2 = 11;

int16_t ax, ay, az;
int16_t gx, gy, gz;
void setup()
{
  Serial.begin(115200);
  while (!compass.begin())
  {
    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
    delay(500);
  }

    if(compass.isHMC()){
        Serial.println("Initialize HMC5883");
        compass.setRange(HMC5883L_RANGE_1_3GA);
        compass.setMeasurementMode(HMC5883L_CONTINOUS);
        compass.setDataRate(HMC5883L_DATARATE_15HZ);
        compass.setSamples(HMC5883L_SAMPLES_8);
    }
   else if(compass.isQMC()){
        Serial.println("Initialize QMC5883");
        compass.setRange(QMC5883_RANGE_2GA);
        compass.setMeasurementMode(QMC5883_CONTINOUS); 
        compass.setDataRate(QMC5883_DATARATE_50HZ);
        compass.setSamples(QMC5883_SAMPLES_8);
   }
   forward();
  }
void loop()
{
  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);
 

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For dehradun/India declination angle is 1'35E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (1 + (35.0 / 60.0)) / (180 / PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading <= 0){
    heading += 2 * PI;
  }

  if (heading >= 2 * PI){
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180/PI; 

  compass.get(&ax,&ay,&az,&gx,&gy,&gz);
  ax=map(ax,-17000,17000,-1500,1500);

  // Output
  Serial.print(" Heading = ");
  Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();

  Vector raw = compass.readRaw();
  //Vector norm = compass.readNormalize();

 // if(headingDegrees>45){
   // forward();
 // }

//  Serial.print(" Xraw = ");
//  Serial.println(raw.XAxis);
//  Serial.print(" Yraw = ");
//  Serial.println(raw.YAxis);
//  Serial.print(" Zraw = ");
//  Serial.println(raw.ZAxis);
 // Serial.print(" Xnorm = ");
  //Serial.println(norm.XAxis);
  //Serial.print(" Ynorm = ");
  //Serial.println(norm.YAxis);
  //Serial.print(" ZNorm = ");
  //Serial.println(norm.ZAxis);
  //Serial.println();  

 // delay(100);

  delay(800);
}

void forward()
{
  digitalWrite(rbm, HIGH);
  digitalWrite(lbm, HIGH);
  digitalWrite(mbr1, LOW);
  digitalWrite(mbr2, LOW);
  digitalWrite(pwm1, HIGH);
  digitalWrite(pwm2, HIGH);
}
