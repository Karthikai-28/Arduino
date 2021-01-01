#include <U8glib.h>
#include <Wire.h> //I2C Arduino Library

#define address 0x1E //0011110b, I2C 7bit address of HMC5883

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

int x,y,z; //triple axis data

char bufferX [20];
char bufferY [20];
char bufferZ [20];

void draw(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 0, 20, bufferX);
  u8g.drawStr( 0, 40, bufferY);
  u8g.drawStr( 0, 60, bufferZ);

}

void setup(void) {
  x = 0;
  y = 0;
  z = 0;
  
  Wire.begin();
  Serial.begin(9600);
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(address); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();

}

void loop(void) {
  //Tell the HMC5883 where to begin reading data
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(address, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  
  sprintf(bufferX, "x : %d", x);
  sprintf(bufferY, "y : %d", y);
  sprintf(bufferZ, "z : %d", z);

  Serial.print(x);
  Serial.print(y);
  Serial.print(z);

  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  delay(100);
}
