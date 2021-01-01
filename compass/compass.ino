#include <Wire.h>
#include <HMC5883L.h>
HMC5883L compass;
void setup()
{
 Serial.begin(9600);
 Wire.begin();
 compass = HMC5883L();
 compass.setScale(1.3);
 compass.setMeasurementMode(HMC5883L_CONTINOUS);
}
void loop()
{
 MagnetometerRaw raw = compass.readRawAxis();
 MagnetometerScaled scaled = compass.readScaledAxis();
 float xHeading = atan2(scaled.YAxis, scaled.XAxis);
 float yHeading = atan2(scaled.ZAxis, scaled.XAxis);
 float zHeading = atan2(scaled.ZAxis, scaled.YAxis);

 Serial.print(xHeading);
 Serial.print(",");
 Serial.print(yHeading);
 Serial.print(",");
 Serial.print(zHeading);
 Serial.println(";");
 delay(500);
}
